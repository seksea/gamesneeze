#include "../../includes.hpp"
#include "hooks.hpp"

void Hooks::FrameStageNotify::hook(void* thisptr, FrameStage frame) {
    Features::ClantagChanger::frameStageNotify(frame);
    original(thisptr, frame);
}