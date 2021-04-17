#include "features.h"
#include "../../includes.hpp"

void Features::SlowWalk::createMove(CUserCmd *cmd) {
    if (Interfaces::engine->IsInGame() && Globals::localPlayer && Globals::localPlayer->health() > 0 && 
            Globals::localPlayer->flags() & (1 << 0) && cmd->buttons & (1 << 17) && CONFIGBOOL("Rage>AntiAim>Slow Walk") &&
            (Globals::localPlayer->velocity().Length2D() > CONFIGINT("Rage>AntiAim>Slow Walk Speed"))) {
        cmd->forwardmove = 0;
        cmd->sidemove = 0;
    }
}
