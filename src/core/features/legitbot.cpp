#include "../../includes.hpp"
#include "features.hpp"
#include <algorithm>

void Features::LegitBot::createMove(CUserCmd* cmd) {
    if ((Menu::CustomWidgets::isKeyDown(CONFIGINT("Legit>LegitBot>Default>Key")) || CONFIGBOOL("Legit>LegitBot>Default>Always on")) &&
            Interfaces::engine->IsInGame() && Globals::localPlayer && Globals::localPlayer->health() > 0) {
        Weapon *weapon = (Weapon *) Interfaces::entityList->GetClientEntity((uintptr_t)Globals::localPlayer->activeWeapon() & 0xFFF); // GetClientEntityFromHandle is being gay
        if (weapon) {
            float smoothing = 1.f + (CONFIGINT("Legit>LegitBot>Default>Smoothing")/2.5f);
            float FOV = CONFIGINT("Legit>LegitBot>Default>FOV")/10.f;

            float rcsX = Globals::localPlayer->aimPunch().x * 2 * CONFIGINT("Legit>LegitBot>Default>RCS Amount Y") / 100; // Flipped because it makes more sense in game this way
            float rcsY = Globals::localPlayer->aimPunch().y * 2 * CONFIGINT("Legit>LegitBot>Default>RCS Amount X") / 100;
            float rcsZ = Globals::localPlayer->aimPunch().z * 2;
            QAngle rcsAngle = QAngle(rcsX, rcsY, rcsZ);

            bool flashCheck = CONFIGBOOL("Legit>LegitBot>Default>Flash Check");
            bool jumpCheck = CONFIGBOOL("Legit>LegitBot>Default>Jump Check");
            bool enemyJumpCheck = CONFIGBOOL("Legit>LegitBot>Default>Enemy Jump Check");

            bool hbHead = CONFIGBOOL("Legit>LegitBot>Default>Head");
            bool hbChest = CONFIGBOOL("Legit>LegitBot>Default>Chest");
            bool hbStomach = CONFIGBOOL("Legit>LegitBot>Default>Stomach");
            bool hbPelvis = CONFIGBOOL("Legit>LegitBot>Default>Pelvis");

            float reactionTime = CONFIGINT("Legit>LegitBot>Default>Reaction Time");
            float maxLockTime = CONFIGINT("Legit>LegitBot>Default>Max Lock Time");

            if ((std::find(std::begin(pistols), std::end(pistols), weapon->itemIndex()) != std::end(pistols)) && CONFIGBOOL("Legit>LegitBot>Pistol>Override")) {
                smoothing = 1.f + (CONFIGINT("Legit>LegitBot>Pistol>Smoothing")/2.5f);
                FOV = CONFIGINT("Legit>LegitBot>Pistol>FOV")/10.f;

                flashCheck = CONFIGBOOL("Legit>LegitBot>Pistol>Flash Check");
                jumpCheck = CONFIGBOOL("Legit>LegitBot>Pistol>Jump Check");
                enemyJumpCheck = CONFIGBOOL("Legit>LegitBot>Pistol>Enemy Jump Check");

                hbHead = CONFIGBOOL("Legit>LegitBot>Pistol>Head");
                hbChest = CONFIGBOOL("Legit>LegitBot>Pistol>Chest");
                hbStomach = CONFIGBOOL("Legit>LegitBot>Pistol>Stomach");
                hbPelvis = CONFIGBOOL("Legit>LegitBot>Pistol>Pelvis");
            }
            else if ((std::find(std::begin(heavyPistols), std::end(heavyPistols), weapon->itemIndex()) != std::end(heavyPistols)) && CONFIGBOOL("Legit>LegitBot>Heavy Pistol>Override")) {
                smoothing = 1.f + (CONFIGINT("Legit>LegitBot>Heavy Pistol>Smoothing")/2.5f);
                FOV = CONFIGINT("Legit>LegitBot>Heavy Pistol>FOV")/10.f;

                flashCheck = CONFIGBOOL("Legit>LegitBot>Heavy Pistol>Flash Check");
                jumpCheck = CONFIGBOOL("Legit>LegitBot>Heavy Pistol>Jump Check");
                enemyJumpCheck = CONFIGBOOL("Legit>LegitBot>Heavy Pistol>Enemy Jump Check");

                hbHead = CONFIGBOOL("Legit>LegitBot>Heavy Pistol>Head");
                hbChest = CONFIGBOOL("Legit>LegitBot>Heavy Pistol>Chest");
                hbStomach = CONFIGBOOL("Legit>LegitBot>Heavy Pistol>Stomach");
                hbPelvis = CONFIGBOOL("Legit>LegitBot>Heavy Pistol>Pelvis");
            }
            else if ((std::find(std::begin(rifles), std::end(rifles), weapon->itemIndex()) != std::end(rifles)) && CONFIGBOOL("Legit>LegitBot>Rifle>Override")) {
                smoothing = 1.f + (CONFIGINT("Legit>LegitBot>Rifle>Smoothing")/2.5f);
                FOV = CONFIGINT("Legit>LegitBot>Rifle>FOV")/10.f;

                rcsX = Globals::localPlayer->aimPunch().x * 2 * CONFIGINT("Legit>LegitBot>Rifle>RCS Amount Y") / 100; // Flipped because it makes more sense in game this way
                rcsY = Globals::localPlayer->aimPunch().y * 2 * CONFIGINT("Legit>LegitBot>Rifle>RCS Amount X") / 100;
                rcsAngle = QAngle(rcsX, rcsY, rcsZ);

                flashCheck = CONFIGBOOL("Legit>LegitBot>Rifle>Flash Check");
                jumpCheck = CONFIGBOOL("Legit>LegitBot>Rifle>Jump Check");
                enemyJumpCheck = CONFIGBOOL("Legit>LegitBot>Rifle>Enemy Jump Check");

                hbHead = CONFIGBOOL("Legit>LegitBot>Rifle>Head");
                hbChest = CONFIGBOOL("Legit>LegitBot>Rifle>Chest");
                hbStomach = CONFIGBOOL("Legit>LegitBot>Rifle>Stomach");
                hbPelvis = CONFIGBOOL("Legit>LegitBot>Rifle>Pelvis");

                reactionTime = CONFIGINT("Legit>LegitBot>Rifle>Reaction Time");
                maxLockTime = CONFIGINT("Legit>LegitBot>Rifle>Max Lock Time");
            }
            else if ((std::find(std::begin(smgs), std::end(smgs), weapon->itemIndex()) != std::end(smgs)) && CONFIGBOOL("Legit>LegitBot>SMG>Override")) {
                smoothing = 1.f + (CONFIGINT("Legit>LegitBot>SMG>Smoothing")/2.5f);
                FOV = CONFIGINT("Legit>LegitBot>SMG>FOV")/10.f;

                rcsX = Globals::localPlayer->aimPunch().x * 2 * CONFIGINT("Legit>LegitBot>SMG>RCS Amount Y") / 100; // Flipped because it makes more sense in game this way
                rcsY = Globals::localPlayer->aimPunch().y * 2 * CONFIGINT("Legit>LegitBot>SMG>RCS Amount X") / 100;
                rcsAngle = QAngle(rcsX, rcsY, rcsZ);

                flashCheck = CONFIGBOOL("Legit>LegitBot>SMG>Flash Check");
                jumpCheck = CONFIGBOOL("Legit>LegitBot>SMG>Jump Check");
                enemyJumpCheck = CONFIGBOOL("Legit>LegitBot>SMG>Enemy Jump Check");

                hbHead = CONFIGBOOL("Legit>LegitBot>SMG>Head");
                hbChest = CONFIGBOOL("Legit>LegitBot>SMG>Chest");
                hbStomach = CONFIGBOOL("Legit>LegitBot>SMG>Stomach");
                hbPelvis = CONFIGBOOL("Legit>LegitBot>SMG>Pelvis");

                reactionTime = CONFIGINT("Legit>LegitBot>SMG>Reaction Time");
                maxLockTime = CONFIGINT("Legit>LegitBot>SMG>Max Lock Time");
            }
            else if ((weapon->itemIndex() == WEAPON_SSG08) && CONFIGBOOL("Legit>LegitBot>Scout>Override")) {
                smoothing = 1.f + (CONFIGINT("Legit>LegitBot>Scout>Smoothing")/2.5f);
                FOV = CONFIGINT("Legit>LegitBot>Scout>FOV")/10.f;

                flashCheck = CONFIGBOOL("Legit>LegitBot>Scout>Flash Check");
                jumpCheck = CONFIGBOOL("Legit>LegitBot>Scout>Jump Check");
                enemyJumpCheck = CONFIGBOOL("Legit>LegitBot>Scout>Enemy Jump Check");

                hbHead = CONFIGBOOL("Legit>LegitBot>Scout>Head");
                hbChest = CONFIGBOOL("Legit>LegitBot>Scout>Chest");
                hbStomach = CONFIGBOOL("Legit>LegitBot>Scout>Stomach");
                hbPelvis = CONFIGBOOL("Legit>LegitBot>Scout>Pelvis");
            }
            else if ((weapon->itemIndex() == WEAPON_AWP) && CONFIGBOOL("Legit>LegitBot>AWP>Override")) {
                smoothing = 1.f + (CONFIGINT("Legit>LegitBot>AWP>Smoothing")/2.5f);
                FOV = CONFIGINT("Legit>LegitBot>AWP>FOV")/10.f;

                flashCheck = CONFIGBOOL("Legit>LegitBot>AWP>Flash Check");
                jumpCheck = CONFIGBOOL("Legit>LegitBot>AWP>Jump Check");
                enemyJumpCheck = CONFIGBOOL("Legit>LegitBot>AWP>Enemy Jump Check");

                hbHead = CONFIGBOOL("Legit>LegitBot>AWP>Head");
                hbChest = CONFIGBOOL("Legit>LegitBot>AWP>Chest");
                hbStomach = CONFIGBOOL("Legit>LegitBot>AWP>Stomach");
                hbPelvis = CONFIGBOOL("Legit>LegitBot>AWP>Pelvis");
            }
            else if ((std::find(std::begin(heavyWeapons), std::end(heavyWeapons), weapon->itemIndex()) != std::end(heavyWeapons)) && CONFIGBOOL("Legit>LegitBot>Heavy>Override")) {
                smoothing = 1.f + (CONFIGINT("Legit>LegitBot>Heavy>Smoothing")/2.5f);
                FOV = CONFIGINT("Legit>LegitBot>Heavy>FOV")/10.f;

                rcsX = Globals::localPlayer->aimPunch().x * 2 * CONFIGINT("Legit>LegitBot>Heavy>RCS Amount Y") / 100; // Flipped because it makes more sense in game this way
                rcsY = Globals::localPlayer->aimPunch().y * 2 * CONFIGINT("Legit>LegitBot>Heavy>RCS Amount X") / 100;
                rcsAngle = QAngle(rcsX, rcsY, rcsZ);

                flashCheck = CONFIGBOOL("Legit>LegitBot>Heavy>Flash Check");
                jumpCheck = CONFIGBOOL("Legit>LegitBot>Heavy>Jump Check");
                enemyJumpCheck = CONFIGBOOL("Legit>LegitBot>Heavy>Enemy Jump Check");

                hbHead = CONFIGBOOL("Legit>LegitBot>Heavy>Head");
                hbChest = CONFIGBOOL("Legit>LegitBot>Heavy>Chest");
                hbStomach = CONFIGBOOL("Legit>LegitBot>Heavy>Stomach");
                hbPelvis = CONFIGBOOL("Legit>LegitBot>Heavy>Pelvis");
            }

            float closestDelta = FLT_MAX;
            QAngle angleToClosestBone;

            // TODO: We should switch to using returns instead of many nested if statements at some point
            //       just incase anyone ever wants to read the code and not have an aneurysm.

            // Enumerate over players and get angle to the closest player to crosshair
            for (int i = 1; i < Interfaces::globals->maxClients; i++) {
                Player* p = (Player*)Interfaces::entityList->GetClientEntity(i);
                if (p && p != Globals::localPlayer) {
                    if (p->health() > 0 && !p->dormant() && p->team() != Globals::localPlayer->team() && p->visible()) {

                        // I know I said I wouldnt use returns, but this just
                        // is not happening using nested if statements

                        // TODO: There is definately a better way to do a flashed check
                        if (flashCheck && Globals::localPlayer->flashDuration() > 0.0f)
                            return;

                        if (jumpCheck && !(Globals::localPlayer->flags() & (1<<0)))
                            return;

                        if (enemyJumpCheck && !(p->flags() & (1<<0)))
                            return;

                        // TODO: What the hell am I doing wrong, idk how to use curtime
                        /*if (reactionTime > 0.f) {
                            float curTime = Interfaces::globals->curtime;
                            const float timeToWait = curTime + (reactionTime / 1000.f);
                            if (curTime < timeToWait)
                                return;
                        }
                        if (maxLockTime > 0.f) {
                            float curTime = Interfaces::globals->curtime;
                            const float timeToWait = curTime + (maxLockTime / 1000.f);
                            if (curTime > maxLockTime)
                                return;
                        }*/

                        matrix3x4_t boneMatrix[128];
                        if (p->getAnythingBones(boneMatrix)) {
                            Vector localPlayerEyePos = Globals::localPlayer->eyePos();

                            std::vector<int> hitboxes = { hbHead ? 8 : 0, hbChest ? 6 : 0, hbStomach ? 5 : 0, hbPelvis ? 3 : 0 };

                            studiohdr_t* model = Interfaces::modelInfo->GetStudioModel(p->model());
                            if (model) {
                                for (int i : hitboxes) {
                                    if (i == 0)
                                        continue;

                                    Vector targetBonePos = p->getBonePos(i);

                                    QAngle angleToCurrentBone = calcAngle(localPlayerEyePos, targetBonePos) - cmd->viewangles - rcsAngle;
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
            if (closestDelta < FOV) {
                if (((angleToClosestBone) / smoothing).Length() > 0.005f) { // prevent micro-movements
                    cmd->viewangles += (angleToClosestBone) / smoothing;
                }
            }
        }
    }
}
