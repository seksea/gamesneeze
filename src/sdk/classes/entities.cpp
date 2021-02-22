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

std::map<int, bool> playersVisible;
void updatePlayersVisible() {
    if (Globals::localPlayer) {
        if (Interfaces::engine->IsInGame()) {
            for (int i = 0; i < Interfaces::globals->maxClients; i++) {
                Player* p = (Player*)Interfaces::entityList->GetClientEntity(i);
                if (p) {
                    if (p->health() > 0 && !p->dormant() && p->team() != Globals::localPlayer->team()) {
                        if (playersVisible.find(i) != playersVisible.end()) {
                            playersVisible[i] = visCheck(p);
                        }
                        else {
                            playersVisible.insert(std::pair<int, bool>(i, visCheck(p)));
                        }
                    }
                }
            }
        }
    }
}

bool Player::visible() {
    if (playersVisible.find(index()) != playersVisible.end()) {
        return playersVisible[index()];
    }
    return false;
}