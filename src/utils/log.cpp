#include "../includes.hpp"

/* print Logs in green */
void Log::log(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    printf("\e[32m[LOG] ");
    vprintf(fmt, args);
    printf("\e[0m\n");
    va_end(args);
}

/* print warns in orange */
void Log::warn(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    printf("\e[33m[WARN] ");
    vprintf(fmt, args);
    printf("\e[0m\n");
    va_end(args);
}

/* print errors in red */
void Log::err(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    printf("\e[31m[ERR] ");
    vprintf(fmt, args);
    printf("\e[0m\n");
    va_end(args);
}