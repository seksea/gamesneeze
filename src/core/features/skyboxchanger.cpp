#include "features.hpp"
#include <cstring>

void Features::SkyboxChanger::frameStageNotify(FrameStage frame) {
    static ConVar* r_3dsky = Interfaces::convar->FindVar("r_3dsky");
    if (frame == FRAME_NET_UPDATE_POSTDATAUPDATE_END) {
        if (CONFIGINT("Visuals>World>World>Skybox")) {
            Offsets::setNamedSkybox((CONFIGINT("Visuals>World>World>Skybox") != 1) ? skyboxes[CONFIGINT("Visuals>World>World>Skybox")] : "sky_l4d_rural02_ldr");
            if (r_3dsky) {
                r_3dsky->SetValue(0);
            }
        }
        else if (r_3dsky) {
            r_3dsky->SetValue(1);
        }
    }
}