#include "../../includes.hpp"

class a {};

bool Interfaces::init() {
    Log::log("initialising interfaces...");

    getInterface<a>("./bin/linux64/engine_client.so", "VEngineClient");

    Log::log("initialised interfaces...");
    return true;
}

bool Interfaces::unload() {
    Log::log("unloading interfaces...");

    Log::log("unloaded interfaces!");
    return true;
}