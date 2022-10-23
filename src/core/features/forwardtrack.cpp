#include "../../includes.hpp"
#include "features.hpp"
#include <cfloat>
#include <cstring>

void Features::Forwardtrack::createMove(CUserCmd* cmd) {
    if (CONFIGBOOL("Legit>Backtrack>Simple Forwardtracking")) {
        // Find how far we should backtrack in this tick
        QAngle viewAngles;
        Interfaces::engine->GetViewAngles(viewAngles);
        viewAngles += Globals::localPlayer->aimPunch() * 2;

        float closestDelta = FLT_MAX;
        int closestTick = cmd->tick_count;

        if (cmd->buttons & (1 << 0)) {
            for (int i = 1; i < Interfaces::globals->maxClients; i++) {
                Player* p = (Player*)Interfaces::entityList->GetClientEntity(i);
                if (p && p->health() > 0 && !p->dormant()) {
                    matrix3x4_t boneMatrix[128];
                    if (p->getAnythingBones(boneMatrix)) {
                        Vector localPlayerEyePos = Globals::localPlayer->eyePos();

                        Vector targetEyePos = Vector(boneMatrix[8][0][3], boneMatrix[8][1][3], boneMatrix[8][2][3]); // 8 is headbone in bonematrix
                        for (int i = 0; i < 2; i++) {
                            targetEyePos += (p->velocity()*Interfaces::globals->interval_per_tick);
                            
                            QAngle angleToCurrentPlayer = calcAngle(localPlayerEyePos, targetEyePos);
                            angleToCurrentPlayer -= viewAngles;
                            if (angleToCurrentPlayer.y > 180.f) {
                                angleToCurrentPlayer.y -= 360.f;
                            }
                            if (angleToCurrentPlayer.Length() < closestDelta) {
                                closestDelta = angleToCurrentPlayer.Length();
                                closestTick = cmd->tick_count+i;
                            }
                        }
                    }
                }
            }
        }
        cmd->tick_count = closestTick;
    }
}