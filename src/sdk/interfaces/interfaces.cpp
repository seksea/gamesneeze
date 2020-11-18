#include "../../includes.hpp"

bool Interfaces::init() {
    Log::log("initialising interfaces...");

    IVEngineClient* engine = getInterface<IVEngineClient>("./bin/linux64/engine_client.so", "VEngineClient");

    Log::log("initialised interfaces...");
    return true;
}

bool Interfaces::unload() {
    Log::log("unloading interfaces...");

    Log::log("unloaded interfaces!");
    return true;
}