#include "../../includes.hpp"
#include "hooks.hpp"
#include <algorithm>



bool Hooks::CreateMove::hook(void* thisptr, float flInputSampleTime, CUserCmd* cmd) {
    original(thisptr, flInputSampleTime, cmd);
    if (cmd && cmd->command_number) {
        
        Globals::localPlayer = (Player*)Interfaces::entityList->GetClientEntity(Interfaces::engine->GetLocalPlayer());

        startMovementFix(cmd);

            Features::RankReveal::createMove(cmd);
            Features::AutoHop::createMove(cmd);
            Features::FastDuck::createMove(cmd);
            
            Features::Backtrack::store(cmd);
            Features::Prediction::start(cmd);
                Features::LegitBot::createMove(cmd);
                Features::Triggerbot::createMove(cmd);
                Features::Backtrack::createMove(cmd);
            Features::Prediction::end();
            Features::Forwardtrack::createMove(cmd);

            if (Features::AutoDefuse::shouldDefuse) {
                cmd->buttons |= (1 << 5);
            }

        endMovementFix(cmd);

        cmd->forwardmove = std::clamp(cmd->forwardmove, -450.0f, 450.0f);
        cmd->sidemove = std::clamp(cmd->sidemove, -450.0f, 450.0f);
        cmd->upmove = std::clamp(cmd->upmove, -320.0f, 320.0f);

        normalizeAngles(cmd->viewangles);
        cmd->viewangles.x = std::clamp(cmd->viewangles.x, -89.0f, 89.0f);
        cmd->viewangles.y = std::clamp(cmd->viewangles.y, -180.0f, 180.0f);
        cmd->viewangles.z = 0.0f;
    }

    return false; // return false when we want to do silent angles for rb
}