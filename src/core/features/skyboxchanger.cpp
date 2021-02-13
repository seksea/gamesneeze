#include "features.hpp"
#include <cstring>

void Features::SkyboxChanger::frameStageNotify(FrameStage frame) {
    if (CONFIGINT("Visuals>World>World>Skybox")) {
        if (frame == FRAME_NET_UPDATE_POSTDATAUPDATE_END) {
            Offsets::setNamedSkybox((CONFIGINT("Visuals>World>World>Skybox") != 1) ? skyboxes[CONFIGINT("Visuals>World>World>Skybox")] : "sky_l4d_rural02_ldr");
        }
    }
}
