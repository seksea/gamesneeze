#include "../../includes.hpp"
#include "interfaces.hpp"
#include <cstdint>
#include <string>

typedef IClientMode* (*getClientModeFunc)();

bool Interfaces::init() {
    Log::log(LOG, "Initialising interfaces...");

    client = getInterface<IBaseClientDLL>("./csgo/bin/linux64/client_client.so", "VClient");
    engine = getInterface<IVEngineClient>("./bin/linux64/engine_client.so", "VEngineClient");
    panel = getInterface<IPanel>("./bin/linux64/vgui2_client.so", "VGUI_Panel");
    entityList = getInterface<IClientEntityList>("./csgo/bin/linux64/client_client.so", "VClientEntityList");
    engineVgui = getInterface<IEngineVGui>("./bin/linux64/engine_client.so", "VEngineVGui");
    modelRender = getInterface<IVModelRender>("./bin/linux64/engine_client.so", "VEngineModel");
    modelInfo = getInterface<IVModelInfo>("./bin/linux64/engine_client.so", "VModelInfoClient");
    materialSystem = getInterface<IMaterialSystem>("./bin/linux64/materialsystem_client.so", "VMaterialSystem");
    sound = getInterface<IEngineSound>("./bin/linux64/engine_client.so", "IEngineSoundClient");
    trace = getInterface<IEngineTrace>("./bin/linux64/engine_client.so", "EngineTraceClient");
	movement = getInterface<IGameMovement>("./csgo/bin/linux64/client_client.so", "GameMovement");
    prediction = getInterface<IPrediction>("./csgo/bin/linux64/client_client.so", "VClientPrediction001", true);

    /* Get IClientMode */
    uintptr_t HudProcessInput = reinterpret_cast<uintptr_t>(getVTable(client)[10]);
	getClientModeFunc getClientMode = reinterpret_cast<getClientModeFunc>(getAbsoluteAddress(HudProcessInput + 11, 1, 5));
    clientMode = getClientMode();
    Log::log(LOG, " ClientMode %lx", (uintptr_t)clientMode);

    /* Get globals */
    uintptr_t hudUpdate = reinterpret_cast<uintptr_t>(getVTable(client)[11]);
	globals = *reinterpret_cast<CGlobalVars**>(getAbsoluteAddress(hudUpdate + 13, 3, 7));
    Log::log(LOG, " Globals %lx", (uintptr_t)globals);

    Log::log(LOG, "Initialised interfaces!");
    return true;
}

bool Interfaces::unload() {
    Log::log(LOG, "Unloading interfaces...");

    Log::log(LOG, "Unloaded interfaces!");
    return true;
}