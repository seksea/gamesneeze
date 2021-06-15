#include "../../includes.hpp"
#include "features.hpp"

void Features::JumpBug::createMove(CUserCmd* cmd) {
     if (CONFIGBOOL("Misc>Misc>Movement>Jump Bug") &&
             Interfaces::inputSystem->IsButtonDown(KEY_SPACE) &&
             (Globals::localPlayer->flags() & FL_ONGROUND || Globals::localPlayer->flags() & FL_PARTIALGROUND) &&
             !(Features::EdgeJump::flagsBackup & FL_ONGROUND || Features::EdgeJump::flagsBackup & FL_PARTIALGROUND)) {
         cmd->buttons |= IN_DUCK;
         cmd->buttons &= ~IN_JUMP;
     }
}
