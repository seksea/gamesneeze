#include "../../includes.hpp"
#include "features.hpp"

void Features::RageBot::createMove(CUserCmd* cmd) {
    if (Interfaces::engine->IsInGame()) {
        if (Globals::localPlayer) {
            if (Globals::localPlayer->isAlive()) {
                if (cmd->buttons & (1 << 0)) {
                    Weapon *weapon = (Weapon *) Interfaces::entityList->GetClientEntity((uintptr_t)Globals::localPlayer->activeWeapon() & 0xFFF); // GetClientEntityFromHandle is being gay
                    if (weapon) {
                        float FOV = CONFIGINT("Rage>RageBot>Default>FOV")/10.f;

                        float closestDelta = FLT_MAX;
                        QAngle angleToClosestPlayer;

                        // Enumerate over players and get angle to the closest player to crosshair
                        for (int i = 1; i < Interfaces::globals->maxClients; i++) {
                            Player* p = (Player*)Interfaces::entityList->GetClientEntity(i);
                            if (p && p != Globals::localPlayer) {
                                if (p->isAlive() && !p->dormant() && p->team() != Globals::localPlayer->team()) {
                                    matrix3x4_t boneMatrix[128];
                                    if (p->getAnythingBones(boneMatrix)) {
                                        Vector localPlayerEyePos = Globals::localPlayer->eyePos();

                                        Vector targetEyePos = p->getBonePos(8); // 8 is headbone in bonematrix

                                        QAngle angleToCurrentPlayer = calcAngle(localPlayerEyePos, targetEyePos) - cmd->viewangles - Globals::localPlayer->aimPunch()*2;
                                        normalizeAngles(angleToCurrentPlayer);

                                        if (angleToCurrentPlayer.Length() < closestDelta) {
                                            closestDelta = angleToCurrentPlayer.Length();
                                            angleToClosestPlayer = angleToCurrentPlayer;
                                        }
                                    }
                                }
                            }
                        }
                        if (closestDelta < FOV) {
                            cmd->viewangles += angleToClosestPlayer;
                        }
                    }
                }
            }
        }
    }
}