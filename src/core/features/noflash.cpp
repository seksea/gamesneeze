#include "features.hpp"

void Features::NoFlash::frameStageNotify(FrameStage frame) {
    if(Interfaces::engine->IsInGame()) {
        if(CONFIGBOOL("Visuals>World>World>No Flash")) {
            *Globals::localPlayer->maxFlashAlpha_ptr() = 0;
        }
        else {
            *Globals::localPlayer->maxFlashAlpha_ptr() = 255;
        }
    }
}