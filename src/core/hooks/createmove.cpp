#include "../../includes.hpp"
#include "hooks.hpp"

bool Hooks::CreateMove::hook(void* thisptr, float flInputSampleTime, CUserCmd* cmd) {
    Globals::localPlayer = (Player*)Interfaces::entityList->GetClientEntity(Interfaces::engine->GetLocalPlayer());

    Features::RankReveal::createMove();
    Features::AutoHop::createMove(cmd);

    return original(thisptr, flInputSampleTime, cmd);
}