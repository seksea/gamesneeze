#include "../../includes.hpp"
#include "features.hpp"
#include <sys/types.h>

void Features::RageBot::createMove(CUserCmd* cmd) {
    if (Interfaces::engine->IsInGame() && Globals::localPlayer && Globals::localPlayer->health() > 0) {
        Weapon *weapon = (Weapon *) Interfaces::entityList->GetClientEntity((uintptr_t)Globals::localPlayer->activeWeapon() & 0xFFF);
        if (weapon) {
            float FOV = CONFIGINT("Rage>RageBot>Default>FOV")/10.f;

            float closestDelta = FLT_MAX;
            QAngle angleToClosestPlayer = {0, 0, 0};
            Player *closestPlayer = nullptr;

            // Enumerate over players and get angle to the closest player to crosshair
            for (int i = 1; i < Interfaces::globals->maxClients; i++) {
                Player* p = (Player*)Interfaces::entityList->GetClientEntity(i);

                if (p && p != Globals::localPlayer) {
                    if (p->health() > 0 && !p->dormant() && p->isEnemy()) {
                        matrix3x4_t boneMatrix[128];
                        if (p->getAnythingBones(boneMatrix)) {
                            Vector localPlayerEyePos = Globals::localPlayer->eyePos();
                            Vector targetBonePos = p->getBonePos(8);
                            
                            //TODO check which bone would be exposed sooner with engine prediction and which would do more damage.
                            if(CONFIGBOOL("Rage>RageBot>Default>ForceBaim")) {
                                if(p->health() <= CONFIGINT("Rage>RageBot>Default>ForceBaimValue")) {
                                    targetBonePos = p->getBonePos(0); // Pelvis
                                } else {
                                    targetBonePos = p->getBonePos(8); // Head
                                }
                            }

                            QAngle angleToCurrentPlayer = calcAngle(localPlayerEyePos, targetBonePos) - cmd->viewangles - Globals::localPlayer->aimPunch()*2;
                            normalizeAngles(angleToCurrentPlayer);

                            if (angleToCurrentPlayer.Length() < closestDelta) {
                                closestDelta = angleToCurrentPlayer.Length();
                                angleToClosestPlayer = angleToCurrentPlayer;
                                closestPlayer = p;
                            }
                        }
                    }
                }
            }
            if (closestDelta < FOV) {
                cmd->viewangles += angleToClosestPlayer;
                if (CONFIGBOOL("Rage>Autoshoot")) {
                    if (std::find(std::begin(rifles), std::end(rifles), weapon->itemIndex() & 0xFFF) != std::end(rifles)
                        || std::find(std::begin(smgs), std::end(smgs), weapon->itemIndex() & 0xFFF) != std::end(smgs)) {
                            if (closestPlayer && closestPlayer->hittable()) {
                                cmd->buttons |= IN_ATTACK;
                            }
                    }                    
                }
            }
        }
    }
}
