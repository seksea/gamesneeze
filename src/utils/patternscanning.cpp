#include <string.h>
#include <link.h>
#include <vector>
#include "utils.hpp"

// original code by dom1n1k and Patrick at GameDeception and yoinked from Fuzion :kekw:
bool compare(const unsigned char* pData, const unsigned char* bMask, const char* szMask)
{
    for (; *szMask; ++szMask, ++pData, ++bMask)
        if (*szMask == 'x' && *pData != *bMask)
            return false;

    return (*szMask) == 0;
}

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

uintptr_t findPattern(uintptr_t dwAddress, uintptr_t dwLen, unsigned char* bMask, const char* szMask)
{
    for (uintptr_t i = 0; i < dwLen; i++)
        if (compare((unsigned char*)(dwAddress + i), bMask, szMask))
            return (uintptr_t)(dwAddress + i);

    return 0;
}

uintptr_t PatternScan::patternScan(const char* moduleName, unsigned char* bMask, const char* szMask) {
    uintptr_t baseAddress;
    size_t memSize;

    if (!getLibraryInformation(moduleName, &baseAddress, &memSize)){
        Log::log(ERR, "Could Not Get info for Module %s\n", moduleName);
        return 0;
    }

    uintptr_t ret = findPattern(baseAddress, memSize, bMask, szMask);
    if( !ret ){
        Log::log(ERR, "Could not find pattern %s in %s\n", szMask, moduleName);
    }
    return ret;
}