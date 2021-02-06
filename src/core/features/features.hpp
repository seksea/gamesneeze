#pragma once
#include "../../includes.hpp"

namespace Features {
    namespace ESP {
        void draw();
    }
    namespace Chams {
        void drawModelExecute(void* thisptr, void* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld);
    }
    namespace RankReveal {
        void createMove(CUserCmd* cmd);
    }
    namespace RecoilCrosshair {
        void draw();
    }
    namespace WorldColorModulate {
        void updateColorModulation();
    }
    namespace ClantagChanger {
        void frameStageNotify(FrameStage frame);
    }
    namespace Spectators {
        void draw();
    }
    namespace PlayerList {
        void draw();
    }
    namespace AutoHop {
        void createMove(CUserCmd* cmd);
    }
    namespace AutoAccept {
        void emitSound(const char* pSoundEntry);
    }
}