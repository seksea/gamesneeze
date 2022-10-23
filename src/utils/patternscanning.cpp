#include <string.h>
#include <link.h>
#include <iterator>
#include <sstream>
#include "utils.hpp"

struct dlinfo_t
{
    const char* library = nullptr;
    uintptr_t address = 0;
    size_t size = 0;
};
std::vector<dlinfo_t> libraries;
// taken form aixxe's cstrike-basehook-linux
bool getLibraryInformation(const char* library, uintptr_t* address, size_t* size) {
    if (libraries.size() == 0) {
        dl_iterate_phdr([] (struct dl_phdr_info* info, size_t, void*) {
            dlinfo_t library_info = {};

            library_info.library = info->dlpi_name;
            library_info.address = info->dlpi_addr + info->dlpi_phdr[0].p_vaddr;
            library_info.size = info->dlpi_phdr[0].p_memsz;

            libraries.push_back(library_info);

            return 0;
        }, nullptr);
    }

    for (const dlinfo_t& current: libraries) {
        if (!strcasestr(current.library, library))
            continue;

        if (address)
            *address = current.address;

        if (size)
            *size = current.size;

        return true;
    }

    return false;
}

std::vector<std::pair<uint8_t, bool>> getPatternData(const std::string &pattern) {
    std::istringstream iss(pattern);
    std::vector<std::pair<uint8_t, bool>> data;

    for (auto &it : std::vector<std::string>{ std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>() }) {
        data.emplace_back(std::strtol(it.c_str(), nullptr, 16), it == "?" || it == "??");
    }

    return data;
}

bool compareBytes(uintptr_t addr, const std::vector<std::pair<uint8_t, bool>> &patternData) {
    for (size_t i = 0; i < patternData.size(); i++) {
        const auto data = patternData.at(i);

        if (data.second) {
            continue;
        }

        if (*(uint8_t*)(addr + i) != data.first) {
            return false;
        }
    }

    return true;
}

std::vector<uintptr_t> PatternScan::findMatches(const std::string &pattern, uintptr_t addr, size_t size) {
    const auto patternData = getPatternData(pattern);
    const auto firstByte = patternData.front();

    if (firstByte.second) {
        throw std::invalid_argument(R"(First pattern byte can't be '?' or '??')");
    }

    if (size < patternData.size()) {
        throw std::invalid_argument("Pattern size can't be greater than scan size");
    }

    std::vector<uintptr_t> data;

    for (size_t i = 0; i <= size - patternData.size(); i++) {
        if (*(uint8_t *)(addr + i) == firstByte.first && compareBytes(addr + i, patternData)) {
            data.emplace_back(addr + i);
        }
    }

    return data;
}

std::vector<uintptr_t> PatternScan::findMatchesInModule(const char* moduleName, const std::string &pattern) {
    uintptr_t baseAddress;
    size_t memSize;

    if (!getLibraryInformation(moduleName, &baseAddress, &memSize)){
        Log::log(ERR, "Could Not Get info for Module %s", moduleName);
        return {0};
    }

    return findMatches(pattern, baseAddress, memSize);
}

uintptr_t PatternScan::findFirstInModule(const char* moduleName, const std::string &pattern) {
    const auto matches = findMatchesInModule(moduleName, pattern);

    if (matches.empty()) {
        return 0;
    }

    return matches.front();
}