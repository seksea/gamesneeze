#include "../../includes.hpp"
#include "hooks.hpp"
#include <algorithm>

bool Hooks::CreateMove::hook(void* thisptr, float flInputSampleTime, CUserCmd* cmd) {
    if (cmd->tick_count != 0) {
        Globals::localPlayer = (Player*)Interfaces::entityList->GetClientEntity(Interfaces::engine->GetLocalPlayer());

        Features::RankReveal::createMove(cmd);
        Features::AutoHop::createMove(cmd);
        Features::FastDuck::createMove(cmd);
        
        Features::Prediction::start(cmd);
            Features::LegitBot::createMove(cmd);
            Features::Triggerbot::createMove(cmd);
            Features::Backtrack::createMove(cmd);
        Features::Prediction::end();
        Features::Forwardtrack::createMove(cmd);

        if (Features::AutoDefuse::shouldDefuse) {
            cmd->buttons |= (1 << 5);
        }
    }

    cmd->viewangles.x = std::clamp(cmd->viewangles.x, -89.0f, 89.0f);
    cmd->viewangles.y = std::clamp(cmd->viewangles.y, -180.0f, 180.0f);
    cmd->viewangles.z = 0.0f;
    return original(thisptr, flInputSampleTime, cmd);
}