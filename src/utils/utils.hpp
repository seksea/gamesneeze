#pragma once
#include <string.h>
#include <link.h>
#include <vector>

enum logLevel {
    LOG,
    WARN,
    ERR
};
namespace Log {
    void log(logLevel level, const char* fmt, ...);
}

inline uintptr_t getAbsoluteAddress(uintptr_t ptr, int offset, int size) {
	return ptr + *reinterpret_cast<int32_t*>(ptr + offset) + size;
};

inline void**& getVTable(void* c, size_t offset = 0) {
	return *reinterpret_cast<void***>((size_t)c + offset);
}

template <typename T>
inline T getVirtualFunc(void* c, size_t i, size_t offset = 0) {
    return reinterpret_cast<T>(getVTable(c, offset)[i]);
}

inline float randFloat(float min, float max) {
    return min + ((((float)rand()) / (float)RAND_MAX) * (max - min));
}
#include "external/stoba.hpp"

#include <string.h>
#include <link.h>
#include <iterator>
#include <sstream>
#include "utils.hpp"


namespace PatternScan {

struct dlinfo_t
{
    const char* library = nullptr;
    uintptr_t address = 0;
    size_t size = 0;
};
inline std::vector<dlinfo_t> libraries;
// taken form aixxe's cstrike-basehook-linux
static bool getLibraryInformation(const char* library, uintptr_t* address, size_t* size) {
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

template <size_t N>
static uintptr_t find(const char* moduleName, const std::array<int, N>& pattern) {
    uintptr_t* baseAddress{nullptr};
    size_t memSize;

    if (!getLibraryInformation(moduleName, baseAddress, &memSize)){
        Log::log(ERR, "Could Not Get info for Module %s", moduleName);
        return 0;
    }

    for (uint64_t i = 0u; i < memSize - N; ++i)
    {
        bool proceed = true;
        for (uint64_t j = 0u; j < N; ++j) {
            if (baseAddress[i + j] != pattern[j] && pattern[j] != -1) {
                proceed = false;
                break;
            }

            if (proceed) {
                return baseAddress[i];
            }
        }
    }

    return 0;
}
}