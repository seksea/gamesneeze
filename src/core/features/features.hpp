#pragma once
#include "../../includes.hpp"

namespace Features {
    namespace ESP {
        void draw();
    }
    namespace Chams {
        void drawModelExecute(void* thisptr, void* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld);
    }
    namespace AutoDefuse {
        inline bool shouldDefuse = false;
        void onBombRender(PlantedC4* bomb);
    }
    namespace Nightmode {
        void onTonemapController(TonemapController* tonemapController);
    }
    namespace RankReveal {
        void createMove(CUserCmd* cmd);
    }
    namespace RecoilCrosshair {
        void frameStageNotify(FrameStage frame);
        void draw();
    }
    namespace WorldColorModulate {
        void updateColorModulation();
    }
    namespace ClantagChanger {
        void frameStageNotify(FrameStage frame);
    }
    namespace SkyboxChanger {
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
    namespace Radar {
        void espPlayerLoop(Player* p);
    }
    namespace FastDuck {
        void createMove(CUserCmd *cmd);
    }
    namespace Triggerbot {
        void createMove(CUserCmd* cmd);
    }
}