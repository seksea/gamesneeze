#include "../../includes.hpp"
#include "hooks.hpp"
#include "../features/features.hpp"

float Hooks::GetViewmodelFOV::hook(void* thisptr) {
    if (CONFIGINT("Visuals>World>World>Viewmodel FOV") != 0) {
        if (Globals::localPlayer && Globals::localPlayer->health() > 0) {
            return CONFIGINT("Visuals>World>World>Viewmodel FOV");
        }
    }

    return original(thisptr);
}
