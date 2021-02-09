#include "features.hpp"

void Features::FastDuck::createMove(CUserCmd* cmd) {
    if (CONFIGBOOL("Misc>Misc>Fast Duck")) {
        if (Globals::localPlayer) {
            if (Globals::localPlayer->health() > 0) {
                cmd->buttons |= (1 << 22);
            }
        }
    }
}