#include "../../includes.hpp"
#include "features.hpp"
#include <cfloat>
#include <cstring>

void Features::LegitBot::createMove(CUserCmd* cmd) {
    if (cmd->tick_count != 0) {
        if (Menu::CustomWidgets::isKeyDown(CONFIGINT("Legit>LegitBot>Default>Key")) || CONFIGBOOL("Legit>LegitBot>Default>Always on")) {
            if (Interfaces::engine->IsInGame()) {
                if (Globals::localPlayer) {
                    // TODO: make these change based on weapon
                    float smoothing = 1.f + (CONFIGINT("Legit>LegitBot>Default>Smoothing")/5.f);
                    float FOV = CONFIGINT("Legit>LegitBot>Default>FOV")/10.f;
                    bool recoilCompensation = CONFIGBOOL("Legit>LegitBot>Default>Recoil Compensation");

                    float closestDelta = FLT_MAX;
                    QAngle angleToClosestPlayer;

                    // Enumerate over players and get angle to the closest player to crosshair
                    for (int i = 1; i < Interfaces::globals->maxClients; i++) {
                        Player* p = (Player*)Interfaces::entityList->GetClientEntity(i);
                        if (p && p != Globals::localPlayer) {
                            if (p->health() > 0 && !p->dormant() && p->team() != Globals::localPlayer->team()) {
                                matrix3x4_t boneMatrix[128];
                                if (p->setupBones(boneMatrix, 128, BONE_USED_BY_ANYTHING, 0)) {
                                    Vector localPlayerEyePos = Globals::localPlayer->origin();
                                    localPlayerEyePos.z += (cmd->buttons & (1 << 2)) ? 46 : 64; // TODO: Properly get eyepos

                                    Vector targetEyePos = Vector(boneMatrix[8][0][3], boneMatrix[8][1][3], boneMatrix[8][2][3]); // 8 is headbone in bonematrix
                                    
                                    QAngle angleToCurrentPlayer = calcAngle(localPlayerEyePos, targetEyePos) - cmd->viewangles - (recoilCompensation ? Globals::localPlayer->aimPunch()*2 : QAngle());
                                    if (angleToCurrentPlayer.y > 180.f) {
                                        angleToCurrentPlayer.y -= 360.f;
                                    }

                                    if (angleToCurrentPlayer.Length() < closestDelta) {
                                        closestDelta = angleToCurrentPlayer.Length();
                                        angleToClosestPlayer = angleToCurrentPlayer;
                                    }
                                }
                            }
                        }
                    }
                    if (closestDelta < FOV) {
                        if (((angleToClosestPlayer) / smoothing).Length() > 0.005f) { // prevent micro-movements
                            cmd->viewangles += (angleToClosestPlayer) / smoothing;
                        }
                    }
                }
            }
        }
    }
}