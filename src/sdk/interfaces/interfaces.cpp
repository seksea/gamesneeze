#include "../../includes.hpp"

bool Interfaces::init() {
    Log::log("initialising interfaces...");

    Log::log("initialised interfaces...");
    return true;
}

bool Interfaces::unload() {
    Log::log("unloading interfaces...");

    Log::log("unloaded interfaces!");
    return true;
}