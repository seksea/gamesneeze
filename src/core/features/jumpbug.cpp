#include "../../includes.hpp"
#include "features.hpp"

void Features::JumpBug::createMove(CUserCmd* cmd) {
     if (CONFIGBOOL("Misc>Misc>Movement>Jump Bug") &&
             //Menu::CustomWidgets::isKeyDown(205) && // Spacebar
             !(Features::EdgeJump::flagsBackup & FL_ONGROUND) &&
             (Globals::localPlayer->flags() & FL_ONGROUND)) {
         cmd->buttons |= IN_DUCK;
         cmd->buttons &= ~IN_JUMP;
     }
}
