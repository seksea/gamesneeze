#include "../../includes.hpp"
#include "hooks.hpp"
#include <algorithm>
#include <cstdint>



bool Hooks::CreateMove::hook(void* thisptr, float flInputSampleTime, CUserCmd* cmd) {
    original(thisptr, flInputSampleTime, cmd);
    if (cmd->tick_count != 0) {
        uintptr_t rbp;
        asm volatile("mov %%rbp, %0" : "=r" (rbp));
        Globals::sendPacket = ((*(bool **)rbp) - 0x18); //https://www.unknowncheats.me/forum/counterstrike-global-offensive/290258-updating-bsendpacket-linux.html

        if (Interfaces::engine->IsInGame()) {
            static ConVar* mat_postprocess_enable = Interfaces::convar->FindVar("mat_postprocess_enable");
            if (mat_postprocess_enable) {
                mat_postprocess_enable->SetValue(!CONFIGBOOL("Misc>Misc>Misc>Disable Post Processing"));
            }
        }

        startMovementFix(cmd);
            Features::RankReveal::createMove(cmd);
            Features::FastDuck::createMove(cmd);
            Features::UseSpam::createMove(cmd);
            Features::Movement::prePredCreateMove(cmd);

            Features::Prediction::start(cmd);
                if (CONFIGBOOL("Rage>Enabled")) {
                    Features::RageBot::createMove(cmd);
                    Features::AntiAim::createMove(cmd);
                }
                else {
                    Features::LegitBot::createMove(cmd);
                    Features::Triggerbot::createMove(cmd);
                    Features::Backtrack::store(cmd);
                    Features::Backtrack::createMove(cmd);
                    Features::Forwardtrack::createMove(cmd);
                }
            Features::Prediction::end();

            Features::Movement::postPredCreateMove(cmd);

            if (Features::AutoDefuse::shouldDefuse) {
                cmd->buttons |= (1 << 5);
            }
        endMovementFix(cmd);
	    Features::SlowWalk::createMove(cmd);
        Features::Movement::edgeBugPredictor(cmd);
        cmd->forwardmove = std::clamp(cmd->forwardmove, -450.0f, 450.0f);
        cmd->sidemove = std::clamp(cmd->sidemove, -450.0f, 450.0f);
        cmd->upmove = std::clamp(cmd->upmove, -320.0f, 320.0f);

        normalizeAngles(cmd->viewangles);
        cmd->viewangles.x = std::clamp(cmd->viewangles.x, -89.0f, 89.0f);
        cmd->viewangles.y = std::clamp(cmd->viewangles.y, -180.0f, 180.0f);
        cmd->viewangles.z = 0.0f;
    }

    return !(CONFIGBOOL("Rage>Enabled")); // return false when we want to do silent angles for rb
}
