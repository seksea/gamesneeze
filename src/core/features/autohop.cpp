#include "features.hpp"

void Features::AutoHop::createMove(CUserCmd* cmd) {
    if (CONFIGBOOL("Misc>Movement>Auto Hop")) {
        if (!(Globals::localPlayer->flags() & (1<<0))) { // need to make macro for FL_* 
            cmd->buttons &= ~(1<<1); // need to make macro for IN_* 
        }
    }
}