#include "features.hpp"

void Features::AutoHop::createMove(CUserCmd* cmd) {
    if (CONFIGBOOL("Misc>Misc>Movement>Auto Hop")) {
        if ((cmd->tick_count % CONFIGINT("Misc>Misc>Movement>Legitness") == 0)) {
            if (!(Globals::localPlayer->flags() & (1<<0))) { // need to make macro for FL_* 
                cmd->buttons &= ~(1<<1); // need to make macro for IN_* 
            }
        }
    }
}