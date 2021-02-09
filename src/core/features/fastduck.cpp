#include "includes.hpp"

void Features::FastDuck::createMove(CUserCmd* cmd) {
    if (CONFIGBOOL("Misc>Misc>Fast Duck")) {
        if (Globals::localPlayer) {
            if (Globals::localPlayer->helath() > 0) {
                cmd->buttons |= IN_BULLRUSH;
            }
        }
    }
}