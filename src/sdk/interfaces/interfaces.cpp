#include "../../includes.hpp"
#include "icvar.hpp"
#include "igameevent.hpp"
#include "interfaces.hpp"
#include <cstdint>
#include <string>

typedef IClientMode* (*getClientModeFunc)();

template <typename T>
static constexpr auto relativeToAbsolute(std::uintptr_t address) noexcept {
    return (T)(address + 4 + *reinterpret_cast<std::int32_t*>(address));
}

bool Interfaces::init() {
    Log::log(LOG, "Initialising interfaces...");

    convar = getInterface<ICvar>("./bin/linux64/materialsystem_client.so", "VEngineCvar"); // do this first so we can log all the interfaces to game console

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
    eventManager = getInterface<IGameEventManager2>("./bin/linux64/engine_client.so", "GAMEEVENTSMANAGER002", true);

    /* Get IClientMode */
    uintptr_t HudProcessInput = reinterpret_cast<uintptr_t>(getVTable(client)[10]);
	getClientModeFunc getClientMode = reinterpret_cast<getClientModeFunc>(getAbsoluteAddress(HudProcessInput + 11, 1, 5));
    clientMode = getClientMode();
    Log::log(LOG, " ClientMode %lx", (uintptr_t)clientMode);

    /* Get globals */
    uintptr_t hudUpdate = reinterpret_cast<uintptr_t>(getVTable(client)[11]);
	globals = *reinterpret_cast<CGlobalVars**>(getAbsoluteAddress(hudUpdate + 13, 3, 7));
    Log::log(LOG, " Globals %lx", (uintptr_t)globals);

    /* Get input (for thirdperson) */
    uintptr_t activateMouse = reinterpret_cast<uintptr_t>(getVTable(client)[16]);
	input = *reinterpret_cast<CInput**>(getAbsoluteAddress(activateMouse, 3, 7));
    Log::log(LOG, " Input %lx", (uintptr_t)input);

    /* Get PlayerResource */
	uintptr_t instructionAddr = PatternScan::findFirstInModule("/client_client.so", " 48 8B 05 ? ? ? ? 55 48 89 E5 48 85 C0 74 10 48");
	_playerResource = reinterpret_cast<PlayerResource**>(getAbsoluteAddress(instructionAddr, 3, 7));
    Log::log(LOG, " PlayerResource %lx", (uintptr_t)_playerResource);

    renderBeams = *relativeToAbsolute<ViewRenderBeams**>(PatternScan::findFirstInModule("/client_client.so", "48 8D 05 ? ? ? ? 48 8B 38 48 8B 07 FF 10 48 8D 05 ? ? ? ? 48 8B 38") + 3); // Credit: danielkrupinski
    Log::log(LOG, " renderBeams %lx", (uintptr_t)renderBeams);

    Log::log(LOG, "Initialised interfaces!");
    return true;
}

bool Interfaces::unload() {
    Log::log(LOG, "Unloading interfaces...");

    Log::log(LOG, "Unloaded interfaces!");
    return true;
}