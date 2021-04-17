#include "features.hpp"
#include <cstring>

void Features::SkyboxChanger::frameStageNotify(FrameStage frame) {
    if (frame == FRAME_NET_UPDATE_POSTDATAUPDATE_END && CONFIGINT("Visuals>World>World>Skybox")) {
        Offsets::setNamedSkybox((CONFIGINT("Visuals>World>World>Skybox") != 1) ? skyboxes[CONFIGINT("Visuals>World>World>Skybox")] : "sky_l4d_rural02_ldr");
        static ConVar* r_3dsky = Interfaces::convar->FindVar("r_3dsky");
        if (r_3dsky) {
            r_3dsky->SetValue(0);
        }
    }
}