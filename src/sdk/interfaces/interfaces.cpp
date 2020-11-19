#include "../../includes.hpp"

typedef IClientMode* (*getClientModeFn)();

bool Interfaces::init() {
    Log::log("initialising interfaces...");

    client = getInterface<IBaseClientDLL>("./csgo/bin/linux64/client_client.so", "VClient");
    engine = getInterface<IVEngineClient>("./bin/linux64/engine_client.so", "VEngineClient");

    
    uintptr_t HudProcessInput = reinterpret_cast<uintptr_t>(getVTable(client)[10]);
	getClientModeFn getClientMode = reinterpret_cast<getClientModeFn>(getAbsoluteAddress(HudProcessInput + 11, 1, 5));
    clientMode = getClientMode();

    Log::log("initialised interfacsdes...");

    std::cout << clientMode;

    Log::log("initialised interfaces...");
    return true;
}

bool Interfaces::unload() {
    Log::log("unloading interfaces...");

    Log::log("unloaded interfaces!");
    return true;
}