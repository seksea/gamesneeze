#include "features.hpp"

void Features::UseSpam::createMove(CUserCmd* cmd) {
    if (CONFIGBOOL("Misc>Misc>Misc>Use Spam") && Menu::CustomWidgets::isKeyDown(CONFIGINT("Misc>Misc>Misc>Use Spam Key"))) {
        if (Globals::localPlayer) {
            if (Globals::localPlayer->health() > 0 && cmd->tick_count % 2 == 0) {
                cmd->buttons |= (1 << 5);
            }
        }
    }
}