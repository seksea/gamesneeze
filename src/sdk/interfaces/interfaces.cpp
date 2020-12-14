#include "../../includes.hpp"
#include "interfaces.hpp"

typedef IClientMode* (*getClientModeFn)();

bool Interfaces::init() {
    Log::log("Initialising interfaces...");

    client = getInterface<IBaseClientDLL>("./csgo/bin/linux64/client_client.so", "VClient");
    engine = getInterface<IVEngineClient>("./bin/linux64/engine_client.so", "VEngineClient");
    panel = getInterface<IPanel>("./bin/linux64/vgui2_client.so", "VGUI_Panel");

    uintptr_t HudProcessInput = reinterpret_cast<uintptr_t>(getVTable(client)[10]);
	getClientModeFn getClientMode = reinterpret_cast<getClientModeFn>(getAbsoluteAddress(HudProcessInput + 11, 1, 5));
    clientMode = getClientMode();
    Log::log(std::string(" ClientMode ") + std::to_string((uintptr_t)clientMode));

    uintptr_t HudUpdate = reinterpret_cast<uintptr_t>(getVTable(client)[11]);
	globals = *reinterpret_cast<CGlobalVars**>(getAbsoluteAddress(HudUpdate + 13, 3, 7));
    Log::log(std::string(" Globals ") + std::to_string((uintptr_t)globals));

    Log::log("Initialised interfaces!");
    return true;
}

bool Interfaces::unload() {
    Log::log("Unloading interfaces...");

    Log::log("Unloaded interfaces!");
    return true;
}