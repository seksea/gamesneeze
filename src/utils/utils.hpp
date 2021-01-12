#pragma once
#include <string>

namespace Log {
    void log(const char* fmt, ...);
    void warn(const char* fmt, ...);
    void err(const char* fmt, ...);
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