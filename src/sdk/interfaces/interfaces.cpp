#include "../../includes.hpp"
#include "interfaces.hpp"
#include <cstdint>
#include <string>

typedef IClientMode* (*getClientModeFunc)();

bool Interfaces::init() {
    Log::log("Initialising interfaces...");

    client = getInterface<IBaseClientDLL>("./csgo/bin/linux64/client_client.so", "VClient");
    engine = getInterface<IVEngineClient>("./bin/linux64/engine_client.so", "VEngineClient");
    panel = getInterface<IPanel>("./bin/linux64/vgui2_client.so", "VGUI_Panel");
    entityList = getInterface<IClientEntityList>("./csgo/bin/linux64/client_client.so", "VClientEntityList");
    engineVgui = getInterface<IEngineVGui>("./bin/linux64/engine_client.so", "VEngineVGui");

    /* Get IClientMode */
    uintptr_t HudProcessInput = reinterpret_cast<uintptr_t>(getVTable(client)[10]);
	getClientModeFunc getClientMode = reinterpret_cast<getClientModeFunc>(getAbsoluteAddress(HudProcessInput + 11, 1, 5));
    clientMode = getClientMode();
    Log::log(" ClientMode %d", (uintptr_t)clientMode);

    /* I know globals isn't technically an interface it just fits in well here :) */
    /* Get globals */
    uintptr_t hudUpdate = reinterpret_cast<uintptr_t>(getVTable(client)[11]);
	globals = *reinterpret_cast<CGlobalVars**>(getAbsoluteAddress(hudUpdate + 13, 3, 7));
    Log::log(" Globals %d", (uintptr_t)globals);

    Log::log("Initialised interfaces!");
    return true;
}

bool Interfaces::unload() {
    Log::log("Unloading interfaces...");

    Log::log("Unloaded interfaces!");
    return true;
}