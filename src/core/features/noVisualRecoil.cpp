#include "features.hpp"
#include "../../sdk/sdk.hpp"

 void Features::noVisualRecoil::frameStageNotify(FrameStage frame) {
     if (Globals::localPlayer) {
        if (CONFIGBOOL("Visuals>Players>LocalPlayer>No Aim Punch")) {
            if (frame == FRAME_RENDER_START) {
                Globals::localPlayer->aimPunchAngle() = Vector{0, 0, 0};
            }
        } 
        if (CONFIGBOOL("Visuals>Players>LocalPlayer>No View Punch")) {
            if (frame == FRAME_RENDER_START) {
                Globals::localPlayer->viewPunchAngle() = Vector{0, 0, 0}
            }
        }
     }
 }