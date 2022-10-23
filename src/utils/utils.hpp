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

namespace PatternScan {
    std::vector<uintptr_t> findMatches(const std::string &pattern, uintptr_t addr, size_t size);
    std::vector<uintptr_t> findMatchesInModule(const char* moduleName, const std::string &pattern);
    uintptr_t findFirstInModule(const char* moduleName, const std::string &pattern);
}