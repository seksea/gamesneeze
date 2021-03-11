#include "features.hpp"

void Features::AutoHop::createMove(CUserCmd* cmd) {
    if (Globals::localPlayer) {
        if (CONFIGBOOL("Misc>Misc>Movement>Auto Hop")) {
            if (CONFIGBOOL("Misc>Misc>Movement>Humanised Bhop")) {
                if (Globals::localPlayer->moveType() != 9) {
                // https://www.unknowncheats.me/forum/counterstrike-global-offensive/333797-humanised-bhop.html
                    static int hopsRestricted = 0;
                    static int hopsHit = 0;
                    if (!(Globals::localPlayer->flags() & (1<<0))) {
                        cmd->buttons &= ~(1<<1);
                        hopsRestricted = 0;
                    }
                    else if ((rand() % 100 > CONFIGINT("Misc>Misc>Movement>Bhop Hitchance") && 
                            hopsRestricted < CONFIGINT("Misc>Misc>Movement>Bhop Max Misses")) || 
                            (CONFIGINT("Misc>Misc>Movement>Bhop Max Hops Hit") > 0 && 
                            hopsHit > CONFIGINT("Misc>Misc>Movement>Bhop Max Hops Hit"))) {
                        cmd->buttons &= ~(1<<1);
                        hopsRestricted++;
                        hopsHit = 0;
                    }
                    else {
                        hopsHit++;
                    }
                }
            }
            else {
                if (!(Globals::localPlayer->flags() & (1<<0))) { // need to make macro for FL_* 
                    cmd->buttons &= ~(1<<1); // need to make macro for IN_* 
                }
            }
        }
    }
}