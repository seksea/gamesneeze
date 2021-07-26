#include "../../includes.hpp"
#include "features.hpp"
#include <algorithm>

void Features::LegitBot::createMove(CUserCmd* cmd) {
    if ((Menu::CustomWidgets::isKeyDown(CONFIGINT("Legit>LegitBot>Default>Key")) || CONFIGBOOL("Legit>LegitBot>Default>Always on")) &&
            Interfaces::engine->IsInGame() && Globals::localPlayer && Globals::localPlayer->health() > 0) {
        Weapon *weapon = (Weapon *) Interfaces::entityList->GetClientEntity((uintptr_t)Globals::localPlayer->activeWeapon() & 0xFFF); // GetClientEntityFromHandle is being gay
        if (weapon) {
            int hitboxes = CONFIGINT("Legit>LegitBot>Default>Hitboxes");
            float smoothing = 1.f + (CONFIGINT("Legit>LegitBot>Default>Smoothing")/5.f);
            float FOV = CONFIGINT("Legit>LegitBot>Default>FOV")/10.f;
            bool recoilCompensation = CONFIGBOOL("Legit>LegitBot>Default>Recoil Compensation");
            bool aimWhileBlind = CONFIGBOOL("Legit>LegitBot>Default>Aim While Blind");

            if ((std::find(std::begin(pistols), std::end(pistols), weapon->itemIndex() & 0xFFF) != std::end(pistols)) && CONFIGBOOL("Legit>LegitBot>Pistol>Override")) {
                hitboxes = CONFIGINT("Legit>LegitBot>Pistol>Hitboxes");
                smoothing = 1.f + (CONFIGINT("Legit>LegitBot>Pistol>Smoothing")/5.f);
                FOV = CONFIGINT("Legit>LegitBot>Pistol>FOV")/10.f;
                recoilCompensation = false;
                aimWhileBlind = CONFIGBOOL("Legit>LegitBot>Pistol>Aim While Blind");
            }
            else if ((std::find(std::begin(heavyPistols), std::end(heavyPistols), weapon->itemIndex() & 0xFFF) != std::end(heavyPistols)) && CONFIGBOOL("Legit>LegitBot>Heavy Pistol>Override")) {
                hitboxes = CONFIGINT("Legit>LegitBot>Heavy Pistol>Hitboxes");
                smoothing = 1.f + (CONFIGINT("Legit>LegitBot>Heavy Pistol>Smoothing")/5.f);
                FOV = CONFIGINT("Legit>LegitBot>Heavy Pistol>FOV")/10.f;
                recoilCompensation = false;
                aimWhileBlind = CONFIGBOOL("Legit>LegitBot>Heavy Pistol>Aim While Blind");
            }
            else if ((std::find(std::begin(rifles), std::end(rifles), weapon->itemIndex() & 0xFFF) != std::end(rifles)) && CONFIGBOOL("Legit>LegitBot>Rifle>Override")) {
                hitboxes = CONFIGINT("Legit>LegitBot>Rifle>Hitboxes");
                smoothing = 1.f + (CONFIGINT("Legit>LegitBot>Rifle>Smoothing")/5.f);
                FOV = CONFIGINT("Legit>LegitBot>Rifle>FOV")/10.f;
                recoilCompensation = CONFIGINT("Legit>LegitBot>Rifle>Recoil Compensation");
                aimWhileBlind = CONFIGBOOL("Legit>LegitBot>Rifle>Aim While Blind");
            }
            else if ((std::find(std::begin(smgs), std::end(smgs), weapon->itemIndex() & 0xFFF) != std::end(smgs)) && CONFIGBOOL("Legit>LegitBot>SMG>Override")) {
                hitboxes = CONFIGINT("Legit>LegitBot>SMG>Hitboxes");
                smoothing = 1.f + (CONFIGINT("Legit>LegitBot>SMG>Smoothing")/5.f);
                FOV = CONFIGINT("Legit>LegitBot>SMG>FOV")/10.f;
                recoilCompensation = CONFIGINT("Legit>LegitBot>SMG>Recoil Compensation");
                aimWhileBlind = CONFIGBOOL("Legit>LegitBot>SMG>Aim While Blind");
            }
            else if (((weapon->itemIndex() & 0xFFF) == WEAPON_SSG08) && CONFIGBOOL("Legit>LegitBot>Scout>Override")) {
                hitboxes = CONFIGINT("Legit>LegitBot>Scout>Hitboxes");
                smoothing = 1.f + (CONFIGINT("Legit>LegitBot>Scout>Smoothing")/5.f);
                FOV = CONFIGINT("Legit>LegitBot>Scout>FOV")/10.f;
                recoilCompensation = false;
                aimWhileBlind = CONFIGBOOL("Legit>LegitBot>Scout>Aim While Blind");
            }
            else if (((weapon->itemIndex() & 0xFFF) == WEAPON_AWP) && CONFIGBOOL("Legit>LegitBot>AWP>Override")) {
                hitboxes = CONFIGINT("Legit>LegitBot>AWP>Hitboxes");
                smoothing = 1.f + (CONFIGINT("Legit>LegitBot>AWP>Smoothing")/5.f);
                FOV = CONFIGINT("Legit>LegitBot>AWP>FOV")/10.f;
                recoilCompensation = false;
                aimWhileBlind = CONFIGBOOL("Legit>LegitBot>AWP>Aim While Blind");
            }
            else if ((std::find(std::begin(heavyWeapons), std::end(heavyWeapons), weapon->itemIndex() & 0xFFF) != std::end(heavyWeapons)) && CONFIGBOOL("Legit>LegitBot>Heavy>Override")) {
                hitboxes = CONFIGINT("Legit>LegitBot>Heavy>Hitboxes");
                smoothing = 1.f + (CONFIGINT("Legit>LegitBot>Heavy>Smoothing")/5.f);
                FOV = CONFIGINT("Legit>LegitBot>Heavy>FOV")/10.f;
                recoilCompensation = CONFIGINT("Legit>LegitBot>Heavy>Recoil Compensation");
                aimWhileBlind = CONFIGBOOL("Legit>LegitBot>Heavy>Aim While Blind");
            }

            float closestDelta = FLT_MAX;
            QAngle angleToClosestBone = {0, 0, 0};

            // NOTE: We should really be using returns more, it cleans up
            //       the code a good bit, and makes it easier to understand
            //       what is going on.

            // Enumerate over players and get angle to the closest player hitbox (that is enabled) to crosshair
            for (int i = 1; i < Interfaces::globals->maxClients; i++) {
                Player* p = (Player*)Interfaces::entityList->GetClientEntity(i);
                if (p && p != Globals::localPlayer) {
                    if (p->health() > 0 && !p->dormant() && p->isEnemy() && p->visible()) {

                        // TODO: There is probably a better way to do this,
                        //       but when I tried making a timer with curtime
                        //       it didn't work. This will do just fine.
                        if (!aimWhileBlind && Globals::localPlayer->flashDuration() > 2.f)
                            return;

                        matrix3x4_t boneMatrix[128];
                        if (p->getAnythingBones(boneMatrix)) {
                            Vector localPlayerEyePos = Globals::localPlayer->eyePos();

                            studiohdr_t* model = Interfaces::modelInfo->GetStudioModel(p->model());
                            if (model) {
                                for (int i = 0; i < 5; i++) { // swap this for for loop of bones selected by player
                                    if (hitboxes & 1 << i) {
                                        // map hitboxes enum to "actual" hitboxes
                                        int hitbox = (1 << i & (int)HitBoxes::HEAD) ? 8 :
                                                     (1 << i & (int)HitBoxes::NECK) ? 7 :
                                                     (1 << i & (int)HitBoxes::CHEST) ? 6 :
                                                     (1 << i & (int)HitBoxes::STOMACH) ? 5 :
                                                     (1 << i & (int)HitBoxes::PELVIS) ? 3 : -1;

                                        Vector targetBonePos = p->getBonePos(hitbox);

                                        QAngle angleToCurrentBone = calcAngle(localPlayerEyePos, targetBonePos) - cmd->viewangles - (recoilCompensation ? Globals::localPlayer->aimPunch()*2 : QAngle(0, 0, 0));

                                        normalizeAngles(angleToCurrentBone);

                                        if (angleToCurrentBone.Length() < closestDelta) {
                                            closestDelta = angleToCurrentBone.Length();
                                            angleToClosestBone = angleToCurrentBone;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (closestDelta < FOV) {
                if (((angleToClosestBone) / smoothing).Length() > 0.005f) { // prevent micro-movements
                    cmd->viewangles += (angleToClosestBone) / smoothing;
                }
            }
        }
    }
}
