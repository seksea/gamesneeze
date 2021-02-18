#include "features.hpp"

void Features::AutoHop::createMove(CUserCmd* cmd) {
    if (CONFIGBOOL("Misc>Misc>Movement>Auto Hop")) {
            if (!(Globals::localPlayer->flags() & (1<<0))) { // need to make macro for FL_* 
                int chanceToHit = rand() % 100 + 1;
                    if (CONFIGITEM("Misc>Misc>Movement>Auto Hop Hitchance") <= chance) {
                        cmd->buttons &= ~(1<<1); // need to make macro for IN_* 
                    }
                    else {
                        return;
                    }
            }
    }
}