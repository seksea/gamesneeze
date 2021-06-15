#include "features.hpp"

void Features::AutoHop::createMove(CUserCmd* cmd) {
    if (Globals::localPlayer) { // Using bhop and jumpbug causes jumpbug to not work
        if (CONFIGBOOL("Misc>Misc>Movement>Auto Hop")) {
            if (Globals::localPlayer->moveType() == 9) return;
            if (CONFIGBOOL("Misc>Misc>Movement>Jump Bug") &&
                Menu::CustomWidgets::isKeyDown(CONFIGINT("Misc>Misc>Movement>Jump Bug Key"))) return;
            if (CONFIGBOOL("Misc>Misc>Movement>Humanised Bhop")) {
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
            else {
                if (!(Globals::localPlayer->flags() & FL_ONGROUND)) {
                    cmd->buttons &= ~IN_JUMP;
                }
            }
        }
    }
}
