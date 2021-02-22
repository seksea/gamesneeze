#include "../../includes.hpp"
#include "hooks.hpp"

void Hooks::FrameStageNotify::hook(void* thisptr, FrameStage frame) {
    Features::ClantagChanger::frameStageNotify(frame);
    Features::SkyboxChanger::frameStageNotify(frame);
    Features::RecoilCrosshair::frameStageNotify(frame);

    if (frame == FRAME_NET_UPDATE_END) {
        updatePlayersVisible();
    }
    original(thisptr, frame);
}