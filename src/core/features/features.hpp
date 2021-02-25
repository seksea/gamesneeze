#pragma once
#include "../../includes.hpp"
#include <vector>

namespace Features {
    namespace Prediction {
        void start(CUserCmd *cmd);
        void end();
    }
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
    namespace LegitBot {
        void createMove(CUserCmd* cmd);
    }
    namespace Backtrack {
        struct BacktrackPlayer {
            matrix3x4_t boneMatrix[128];
            int playerIndex;
        };

        struct BackTrackTick {
            std::map<int, BacktrackPlayer> players;
            int tickCount;
        };

        inline std::vector<BackTrackTick> backtrackTicks;

        void store(CUserCmd* cmd);
        void createMove(CUserCmd* cmd);
    }
    namespace Forwardtrack {
        void createMove(CUserCmd* cmd);
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
    namespace Notifications {
        void draw();
        void addNotification(ImColor color, const char* fmt, ...);
    }
    namespace FlappyBird {
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