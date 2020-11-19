#include "../../includes.hpp"

bool Interfaces::init() {
    Log::log("initialising interfaces...");

    client = getInterface<IBaseClientDLL>("./csgo/bin/linux64/client_client.so", "VClient");
    engine = getInterface<IVEngineClient>("./bin/linux64/engine_client.so", "VEngineClient");

    Log::log("initialised interfaces...");
    return true;
}

bool Interfaces::unload() {
    Log::log("unloading interfaces...");

    Log::log("unloaded interfaces!");
    return true;
}