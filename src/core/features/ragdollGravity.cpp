#include "features.hpp"
#include <cstring>

void Features::RagdollGravity::frameStageNotify(FrameStage frame) {
    if (frame == FRAME_NET_UPDATE_POSTDATAUPDATE_END){
        static ConVar* cl_ragdoll_gravity = Interfaces::convar->FindVar("cl_ragdoll_gravity");
        if (CONFIGBOOL("Visuals>World>World>Ragdoll Gravity")) {
            cl_ragdoll_gravity->SetValue(-600);
        }
        else {
            cl_ragdoll_gravity->SetValue(600);
        }
    }
}