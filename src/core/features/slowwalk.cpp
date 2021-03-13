#include "features.h"
#include "../../includes.hpp"

void Features::SlowWalk::createMove(CUserCmd *cmd) {
    if (CONFIGBOOL("Rage>AntiAim>Slow Walk")) {
        if (Interfaces::engine->IsInGame()) {
            if (Globals::localPlayer->isAlive()) {
                if (Globals::localPlayer->flags() & (1 << 0)) {
                    //I think 18 is walking idk
                    if (cmd->buttons & (1 << 17)) {
                        if (Globals::localPlayer->velocity().Length2D() > CONFIGINT("Rage>AntiAim>Slow Walk Speed")) {
                            cmd->forwardmove = 0;
                            cmd->sidemove = 0;
                        }
                    }
                }
            }
        }
    }
}
