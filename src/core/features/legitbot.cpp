#include "../../includes.hpp"
#include "features.hpp"
#include <cfloat>
#include <cstring>
#include <iterator>
#include <algorithm>

void Features::LegitBot::createMove(CUserCmd* cmd) {
    if (Menu::CustomWidgets::isKeyDown(CONFIGINT("Legit>LegitBot>Default>Key")) || CONFIGBOOL("Legit>LegitBot>Default>Always on")) {
        if (Interfaces::engine->IsInGame()) {
            if (Globals::localPlayer) {
                if (Globals::localPlayer->health() > 0) {
                    Weapon *weapon = (Weapon *) Interfaces::entityList->GetClientEntity((uintptr_t)Globals::localPlayer->activeWeapon() & 0xFFF); // GetClientEntityFromHandle is being gay
                    if (weapon) {
                        float smoothing = 1.f + (CONFIGINT("Legit>LegitBot>Default>Smoothing")/5.f);
                        float FOV = CONFIGINT("Legit>LegitBot>Default>FOV")/10.f;
                        bool recoilCompensation = CONFIGBOOL("Legit>LegitBot>Default>Recoil Compensation");

                        if ((std::find(std::begin(pistols), std::end(pistols), weapon->itemIndex()) != std::end(pistols)) && CONFIGBOOL("Legit>LegitBot>Pistol>Override")) {
                            smoothing = 1.f + (CONFIGINT("Legit>LegitBot>Pistol>Smoothing")/5.f);
                            FOV = CONFIGINT("Legit>LegitBot>Pistol>FOV")/10.f;
                            recoilCompensation = false;
                        }
                        else if ((std::find(std::begin(heavyPistols), std::end(heavyPistols), weapon->itemIndex()) != std::end(heavyPistols)) && CONFIGBOOL("Legit>LegitBot>Heavy Pistol>Override")) {
                            smoothing = 1.f + (CONFIGINT("Legit>LegitBot>Heavy Pistol>Smoothing")/5.f);
                            FOV = CONFIGINT("Legit>LegitBot>Heavy Pistol>FOV")/10.f;
                            recoilCompensation = false;
                        }
                        else if ((std::find(std::begin(rifles), std::end(rifles), weapon->itemIndex()) != std::end(rifles)) && CONFIGBOOL("Legit>LegitBot>Rifle>Override")) {
                            smoothing = 1.f + (CONFIGINT("Legit>LegitBot>Rifle>Smoothing")/5.f);
                            FOV = CONFIGINT("Legit>LegitBot>Rifle>FOV")/10.f;
                            recoilCompensation = CONFIGINT("Legit>LegitBot>Rifle>Recoil Compensation");
                        }
                        else if ((std::find(std::begin(smgs), std::end(smgs), weapon->itemIndex()) != std::end(smgs)) && CONFIGBOOL("Legit>LegitBot>SMG>Override")) {
                            smoothing = 1.f + (CONFIGINT("Legit>LegitBot>SMG>Smoothing")/5.f);
                            FOV = CONFIGINT("Legit>LegitBot>SMG>FOV")/10.f;
                            recoilCompensation = CONFIGINT("Legit>LegitBot>SMG>Recoil Compensation");
                        }
                        else if ((weapon->itemIndex() == WEAPON_SSG08) && CONFIGBOOL("Legit>LegitBot>Scout>Override")) {
                            smoothing = 1.f + (CONFIGINT("Legit>LegitBot>Scout>Smoothing")/5.f);
                            FOV = CONFIGINT("Legit>LegitBot>Scout>FOV")/10.f;
                            recoilCompensation = false;
                        }
                        else if ((weapon->itemIndex() == WEAPON_AWP) && CONFIGBOOL("Legit>LegitBot>AWP>Override")) {
                            smoothing = 1.f + (CONFIGINT("Legit>LegitBot>AWP>Smoothing")/5.f);
                            FOV = CONFIGINT("Legit>LegitBot>AWP>FOV")/10.f;
                            recoilCompensation = false;
                        }
                        else if ((std::find(std::begin(heavyWeapons), std::end(heavyWeapons), weapon->itemIndex()) != std::end(heavyWeapons)) && CONFIGBOOL("Legit>LegitBot>Heavy>Override")) {
                            smoothing = 1.f + (CONFIGINT("Legit>LegitBot>Heavy>Smoothing")/5.f);
                            FOV = CONFIGINT("Legit>LegitBot>Heavy>FOV")/10.f;
                            recoilCompensation = CONFIGINT("Legit>LegitBot>Heavy>Recoil Compensation");
                        }

                        float closestDelta = FLT_MAX;
                        QAngle angleToClosestPlayer;

                        // Enumerate over players and get angle to the closest player to crosshair
                        for (int i = 1; i < Interfaces::globals->maxClients; i++) {
                            Player* p = (Player*)Interfaces::entityList->GetClientEntity(i);
                            if (p && p != Globals::localPlayer) {
                                if (p->health() > 0 && !p->dormant() && p->team() != Globals::localPlayer->team() && p->visible()) {
                                    matrix3x4_t boneMatrix[128];
                                    if (p->getAnythingBones(boneMatrix)) {
                                        Vector localPlayerEyePos = Globals::localPlayer->eyePos();

                                        Vector targetEyePos = p->getBonePos(8); // 8 is headbone in bonematrix
                                        targetEyePos+=(p->velocity()*Interfaces::globals->interval_per_tick);

                                        QAngle angleToCurrentPlayer = calcAngle(localPlayerEyePos, targetEyePos) - cmd->viewangles - (recoilCompensation ? Globals::localPlayer->aimPunch()*2 : QAngle(0, 0, 0));
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
                            if (((angleToClosestPlayer) / smoothing).Length() > 0.005f) { // prevent micro-movements
                                cmd->viewangles += (angleToClosestPlayer) / smoothing;
                            }
                        }
                    }
                }
            }
        }
    }
}