#include "../../includes.hpp"
#include "hooks.hpp"

bool Hooks::CreateMove::hook(void* thisptr, float flInputSampleTime, CUserCmd* cmd) {
    Globals::localPlayer = (Player*)Interfaces::entityList->GetClientEntity(Interfaces::engine->GetLocalPlayer());

    Features::RankReveal::createMove(cmd);
    Features::AutoHop::createMove(cmd);
    Features::FastDuck::createMove(cmd);
    Features::Triggerbot::createMove(cmd);
    Features::Backtrack::createMove(cmd);
    Features::LegitBot::createMove(cmd);

    if (Features::AutoDefuse::shouldDefuse) {
        cmd->buttons |= (1 << 5);
    }
    return original(thisptr, flInputSampleTime, cmd);
}