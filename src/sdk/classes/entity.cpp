#include "../../includes.hpp"
#include "entity.hpp"
#include "vector.h"

bool visCheck(Player* player) {
    Ray ray;
    Trace traceToPlayer;
    ray.Init(Globals::localPlayer->eyePos(), player->eyePos());
    TraceFilter filter;
    filter.pSkip = Globals::localPlayer;
                                  // solid|opaque|moveable|ignore nodraw
    Interfaces::trace->TraceRay(ray, (0x1 | 0x80 | 0x4000 |    0x2000   ), &filter, &traceToPlayer);
    return (traceToPlayer.m_pEntityHit == player) && !Offsets::lineGoesThroughSmoke(Globals::localPlayer->eyePos(), player->eyePos(), 1);
}

struct PlayerCache {
    bool visible;
    matrix3x4_t boneMatrixHitbox[128];
    matrix3x4_t boneMatrixAnything[128];
};

std::map<int, PlayerCache> playerCache;

void cachePlayers() {
    // ran in framestage notify update_end
    if (Globals::localPlayer) {
        if (Interfaces::engine->IsInGame()) {
            for (int i = 1; i < Interfaces::globals->maxClients; i++) {
                Player* p = (Player*)Interfaces::entityList->GetClientEntity(i);
                if (p) {
                    if (p->health() > 0 && !p->dormant() && p->team() != Globals::localPlayer->team()) {
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
                }
            }
        }
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