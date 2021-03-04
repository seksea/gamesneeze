#include "features.h"
#include "../../includes.hpp"

void Features::SlowWalk::createMove(CUserCmd *cmd) {
    if (CONFIGBOOL("Rage>Slow Walk")) {
        if (Interfaces::engine->IsInGame()) {
            if (Globals::localPlayer->health() > 0) {
                //I think 18 is walking idk
                if (cmd->buttons & (1 << 17)) {
                    if (Globals::localPlayer->velocity().Length2D() > 55) {
                        cmd->forwardmove = 0;
                        cmd->sidemove = 0;
                    }
                }
            }
        }
    }
}
