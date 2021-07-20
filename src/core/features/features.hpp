#pragma once
#include "../../includes.hpp"
#include <vector>

namespace Features {
    namespace Prediction {
        inline bool inPrediction;
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
    namespace SkinChanger {
        void frameStageNotify(FrameStage frame);
    }
    namespace LegitBot {
        void createMove(CUserCmd* cmd);
    }
    namespace Backtrack {
        struct BacktrackPlayer {
            matrix3x4_t boneMatrix[128];
            int playerIndex;
            int playerFlags;
            float playerVelocity;
            Vector playerHeadPos;
        };

        struct BackTrackTick {
            std::map<int, BacktrackPlayer> players;
            int tickCount;
        };

        inline int lastBacktrack;
        inline std::vector<BackTrackTick> backtrackTicks;

        void store(CUserCmd* cmd);
        void createMove(CUserCmd* cmd);
    }
    namespace Forwardtrack {
        void createMove(CUserCmd* cmd);
    }
    namespace ColorModulation {
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
    namespace UseSpam {
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
    namespace RageBot {
        void createMove(CUserCmd* cmd);
    }
    namespace AntiAim {
        inline matrix3x4_t fakeBones[128];
        inline float fakeYaw;
        void createMove(CUserCmd* cmd);
    }
    namespace Hitmarkers {
        struct DamageMarker {
            float drawHitmarkerTill;
            Vector position;
            bool headshot;
            int damage;
        };

        inline std::vector<DamageMarker> damageMarkers;
        inline float drawHitmarkerTill;
        void draw();
    }
    namespace SlowWalk {
        void createMove(CUserCmd* cmd);
    }
    namespace NoFlash {
        void frameStageNotify(FrameStage frame);
    }
    namespace RagdollGravity {
        void frameStageNotify(FrameStage frame);
    }
    namespace NoVisualRecoil {
        void frameStageNotify(FrameStage frame);
    }
    namespace BulletTracers {
        void event(IGameEvent* event);
    }
    namespace Movement {
        inline int flagsBackup;
        inline Vector velBackup;
        inline bool allowBhop = true;
        inline bool shouldEdgebug;
        inline Vector edgebugPos;
        void prePredCreateMove(CUserCmd* cmd);
        void postPredCreateMove(CUserCmd* cmd);
        void edgeBugPredictor(CUserCmd* cmd);
        void draw();
    }
}
