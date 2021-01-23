#include "../includes.hpp"

/* print Logs in green */
void Log::log(logLevel level, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    switch (level) {
        case LOG: printf("\e[32m[LOG] "); break;
        case WARN: printf("\e[33m[WARN] "); break;
        case ERR: printf("\e[31m[ERR] "); break;
    }
    vprintf(fmt, args);
    printf("\e[0m\n");
    va_end(args);
}