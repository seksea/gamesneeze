#include "../../includes.hpp"
#include "entity.hpp"
#include "vector.h"
#include <vector>

bool Player::isEnemy() { // team check that accounts for dangerzone teams
    if (strstr(Offsets::getLocalClient(-1)->m_szLevelNameShort, "dz_")) {
        return (Globals::localPlayer->survivalTeam() == -1) ? true : (Globals::localPlayer->survivalTeam() != this->survivalTeam());
    }
	return this->team() != Globals::localPlayer->team();
}

bool visCheck(Player* player) {
    matrix3x4_t boneMatrix[128];
    if (player->getAnythingBones(boneMatrix)) {
        TraceFilter filter;
        filter.pSkip = Globals::localPlayer;


        Trace traceToHead;
        Ray rayToHead;
        rayToHead.Init(Globals::localPlayer->eyePos(), player->getBonePos(8));
                                    // solid|opaque|moveable|ignore nodraw
        Interfaces::trace->TraceRay(rayToHead, (0x1 | 0x80 | 0x4000 |    0x2000   ), &filter, &traceToHead);

        Trace traceToUpperSpinal;
        Ray rayToUpperSpinal;
        rayToUpperSpinal.Init(Globals::localPlayer->eyePos(), player->getBonePos(6));
                                    // solid|opaque|moveable|ignore nodraw
        Interfaces::trace->TraceRay(rayToUpperSpinal, (0x1 | 0x80 | 0x4000 |    0x2000   ), &filter, &traceToUpperSpinal);

        return (traceToHead.m_pEntityHit == player) && (traceToUpperSpinal.m_pEntityHit == player) && !Offsets::lineGoesThroughSmoke(Globals::localPlayer->eyePos(), player->eyePos(), 1);
    }
    return false;
}

struct PlayerCache {
    bool visible;
    matrix3x4_t boneMatrixHitbox[128];
    matrix3x4_t boneMatrixAnything[128];
};

std::map<int, PlayerCache> playerCache;

void cachePlayers() {
    // ran in framestagenotify
    if (Globals::localPlayer) {
        if (Interfaces::engine->IsInGame()) {
            int highest = Interfaces::entityList->GetHighestEntityIndex();
            for (int i = 1; i < highest; i++) {
                if (i < Interfaces::globals->maxClients) {
                    Player* p = (Player*)Interfaces::entityList->GetClientEntity(i);
                    if (p && p != Globals::localPlayer) {
                        if (p->health() > 0 && !p->dormant()) {
                            PlayerCache player;
                            if (p->setupBones(player.boneMatrixHitbox, 128, BONE_USED_BY_HITBOX, Interfaces::globals->curtime)) {
                                if (p->setupBones(player.boneMatrixAnything, 128, BONE_USED_BY_ANYTHING, Interfaces::globals->curtime)) {
                                    player.visible = visCheck(p);
                                    if (playerCache.find(i) != playerCache.end()) {
                                        playerCache[i] = player;
                                    }
                                    else {
                                        playerCache.insert(std::pair<int, PlayerCache>(i, player));
                                    }
                                }
                            }
                        }
                        else {
                            if (playerCache.find(i) != playerCache.end()) {
                                playerCache.erase(i);
                            }
                        }
                    }
                    else {
                        if (playerCache.find(i) != playerCache.end()) {
                            playerCache.erase(i);
                        }
                    }
                }
                Entity* p = (Entity*)Interfaces::entityList->GetClientEntity(i);
                if (p) {
                    if (!p->dormant()) {
                        for (auto& item : entityDistanceMap) {
                            if (item.second == i) {
                                entityDistanceMap.erase(item.first);
                            }
                        }

                                    // This line contains a really hacky way of ensuring the fog controller stays in the entity distance map 
                                    // as there are other entities that are also at 0, 0, 0 so we just move fog controller to -1, -1, -1
                        entityDistanceMap.insert(std::pair<float, int>(getDistance(Globals::localPlayer->origin(), 
                                                p->clientClass()->m_ClassID == EClassIds::CFogController ? Vector(-1, -1, -1) : p->origin()), i));
                    }
                }
            }
        }
    }
}

Vector Player::getBonePos(int bone) {
    // get cached bonematrix from setupbones we got in fsn
    if (playerCache.find(index()) != playerCache.end()) {
        return Vector(playerCache[index()].boneMatrixAnything[bone][0][3], 
                      playerCache[index()].boneMatrixAnything[bone][1][3], 
                      playerCache[index()].boneMatrixAnything[bone][2][3]);
    }
}

bool Player::getHitboxBones(matrix3x4_t* boneMatrix) {
    // get cached bonematrix from setupbones we got in fsn
    if (playerCache.find(index()) != playerCache.end()) {
        memcpy(boneMatrix, playerCache[index()].boneMatrixHitbox, sizeof(matrix3x4_t)*128);
        return boneMatrix;
    }
    return false;
}

bool Player::getAnythingBones(matrix3x4_t* boneMatrix) {
    // get cached bonematrix from setupbones we got in fsn
    if (playerCache.find(index()) != playerCache.end()) {
        memcpy(boneMatrix, playerCache[index()].boneMatrixAnything, sizeof(matrix3x4_t)*128);
        return boneMatrix;
    }
    return false;
}

bool Player::visible() {
    if (playerCache.find(index()) != playerCache.end()) {
        return playerCache[index()].visible;
    }
    return false;
}