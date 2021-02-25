#include "../../includes.hpp"
#include "hooks.hpp"
#include <algorithm>

QAngle originalAngle;
float originalForwardMove, originalSideMove, originalUpMove;

void startMovementFix(CUserCmd* cmd) {
    originalAngle = cmd->viewangles;
    originalForwardMove = cmd->forwardmove;
    originalSideMove = cmd->sidemove;
}

void endMovementFix(CUserCmd* cmd) {
    // this was just taken from designer bc im lazy
    // https://github.com/designer1337/csgo-cheat-base/blob/09fa2ba8de52eef482bbc82f682976e369191077/dependencies/math/math.cpp#L4
    float deltaViewAngles;
	float f1;
	float f2;

	if (originalAngle.y < 0.f)
		f1 = 360.0f + originalAngle.y;
	else
		f1 = originalAngle.y;

	if (cmd->viewangles.y < 0.0f)
		f2 = 360.0f + cmd->viewangles.y;
	else
		f2 = cmd->viewangles.y;

	if (f2 < f1)
		deltaViewAngles = abs(f2 - f1);
	else
		deltaViewAngles = 360.0f - abs(f1 - f2);

	deltaViewAngles = 360.0f - deltaViewAngles;

	cmd->forwardmove = cos(DEG2RAD(deltaViewAngles)) * originalForwardMove + cos(DEG2RAD(deltaViewAngles + 90.f)) * originalSideMove;
	cmd->sidemove = sin(DEG2RAD(deltaViewAngles)) * originalForwardMove + sin(DEG2RAD(deltaViewAngles + 90.f)) * originalSideMove;
}

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