#include "../includes.hpp"

/* print Logs in green */
void Log::log(std::string str) {
    std::cout << "\e[32m[LOG]" << str.c_str() << "\e[0m\n";
}

/* print warns in orange */
void Log::warn(std::string str) {
    std::cout << "\e[33m[WARN]" << str.c_str() << "\e[0m\n";
}

/* print errors in red */
void Log::err(std::string str) {
    std::cout << "\e[31m[ERR]" << str.c_str() << "\e[0m\n";
}