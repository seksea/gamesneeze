#include "features.hpp"

void Features::FastDuck::createMove(CUserCmd* cmd) {
    if (CONFIGBOOL("Misc>Misc>Movement>Fast Duck")) {
        if (Globals::localPlayer) {
            if (Globals::localPlayer->isAlive()) {
                cmd->buttons |= (1 << 22);
            }
        }
    }
}