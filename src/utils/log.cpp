#include "../includes.hpp"

/* print Logs in green */
void Log::log(logLevel level, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    switch (level) {
        case LOG: fputs("\e[32m[LOG] ", stdout); break;
        case WARN: fputs("\e[33m[WARN] ", stdout); break;
        case ERR: fputs("\e[31m[ERR] ", stdout); break;
    }
    vprintf(fmt, args);
    fputs("\e[0m\n", stdout);
    va_end(args);
}