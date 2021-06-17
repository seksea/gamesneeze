#include "features.hpp"

void Features::NoFlash::frameStageNotify(FrameStage frame) {
    if(Interfaces::engine->IsInGame() && Globals::localPlayer) {
        *Globals::localPlayer->maxFlashAlpha_ptr() = CONFIGBOOL("Visuals>World>World>No Flash") ? CONFIGINT("Visuals>World>World>No Flash Amount") : 255;
    }
}