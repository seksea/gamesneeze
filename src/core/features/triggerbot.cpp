#include "features.hpp"
#include <vector>

Entity* findPlayerThatRayHits(Vector start, Vector end, Trace* traceToPlayer) {
    Ray ray;
    ray.Init(start, end);
    TraceFilter filter;
    filter.pSkip = Globals::localPlayer;
                                    //   hitbox  |  monster  | solid
    Interfaces::trace->TraceRay(ray, (0x40000000 | 0x40000 | 0x1), &filter, traceToPlayer);

    return traceToPlayer->m_pEntityHit;
}

void Features::Triggerbot::createMove(CUserCmd* cmd) {
    if (CONFIGBOOL("Legit>Triggerbot>Triggerbot")) {
        if (Menu::CustomWidgets::isKeyDown(CONFIGINT("Legit>Triggerbot>Key"))) {
            if (Globals::localPlayer) {
                Weapon *weapon = (Weapon *) Interfaces::entityList->GetClientEntity((uintptr_t)Globals::localPlayer->activeWeapon() & 0xFFF); // GetClientEntityFromHandle is being gay
                if (weapon) {

                    QAngle viewAngles;
                    Interfaces::engine->GetViewAngles(viewAngles);
                    viewAngles += Globals::localPlayer->aimPunch() * 2;
                    
                    Vector endPos;
                    Trace traceToPlayer;
                    int headHitchance = 0;
                    int bodyHitchance = 0;

                    float spread = RAD2DEG(weapon->GetInaccuracy() + weapon->GetSpread()) * 1.2; // I have 0 clue where this 1.2 comes from, the angle this makes is smaller than the actual spread circle by a bit and 1.2 corrects it pretty much perfectly
                    for (int i = 0; i < 100; i++) {
                        QAngle randomSpreadAngle = {
                                randFloat(0, spread) - (spread / 2),
                                randFloat(0, spread) - (spread / 2),
                                randFloat(0, spread) - (spread / 2)};
                        
                        angleVectors(viewAngles+randomSpreadAngle, endPos);
                        
                        endPos = Globals::localPlayer->eyePos() + (endPos*4096);

                        Entity* ent = findPlayerThatRayHits(Globals::localPlayer->eyePos(), endPos, &traceToPlayer);
                        if (ent) {
                            if (ent->clientClass()->m_ClassID == CCSPlayer) {
                                if (!ent->dormant()) {
                                    if (ent->team() != Globals::localPlayer->team()) {
                                        switch (traceToPlayer.hitgroup) {
                                        case HITGROUP_HEAD:
                                            headHitchance++;
                                            break;
                                        case HITGROUP_CHEST:
                                        case HITGROUP_STOMACH:
                                            bodyHitchance++;
                                            break;
                                        default:
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    
                    static bool shotLastTick = false;
                    if (CONFIGINT("Legit>Triggerbot>Head Hitchance") && headHitchance >= CONFIGINT("Legit>Triggerbot>Head Hitchance") && !shotLastTick) {
                        cmd->buttons |= (1 << 0);
                        shotLastTick = true;
                    }
                    else if (CONFIGINT("Legit>Triggerbot>Body Hitchance") && bodyHitchance >= CONFIGINT("Legit>Triggerbot>Body Hitchance") && !shotLastTick) {
                        cmd->buttons |= (1 << 0);
                        shotLastTick = true;
                    }
                    else {
                        shotLastTick = false;
                    }
                }
            }
        }
    }
}