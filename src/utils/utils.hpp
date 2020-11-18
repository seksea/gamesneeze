#pragma once

namespace Log {
    void log(std::string str);
    void warn(std::string str);
    void err(std::string str);
}

template <typename T>
inline T getVirtualFunc( void* c, unsigned long i, unsigned long offset = 0) {
    return reinterpret_cast<T>((*reinterpret_cast<void***>((unsigned long)c + offset))[i]);
}