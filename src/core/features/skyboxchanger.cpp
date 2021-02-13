#include "features.hpp"
#include <cstring>

void Features::SkyboxChanger::frameStageNotify(FrameStage frame) {
    if (CONFIGINT("Visuals>World>World>Skybox")) {
        if (frame == FRAME_NET_UPDATE_POSTDATAUPDATE_END) {
            Offsets::setNamedSkybox(skyboxes[CONFIGINT("Visuals>World>World>Skybox")]);
        }
    }
