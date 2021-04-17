#include "features.hpp"

void Features::UseSpam::createMove(CUserCmd* cmd) {
    if (Globals::localPlayer && Globals::localPlayer->health() > 0 && cmd->tick_count % 2 == 0 && CONFIGBOOL("Misc>Misc>Misc>Use Spam") && Menu::CustomWidgets::isKeyDown(CONFIGINT("Misc>Misc>Misc>Use Spam Key"))) {
        cmd->buttons |= (1 << 5);
    }
}