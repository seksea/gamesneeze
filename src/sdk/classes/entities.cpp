#include "../../includes.hpp"
#include "entity.hpp"
#include "vector.h"

bool visCheck(Player* player) {
    Ray ray;
    Trace traceToPlayer;
    ray.Init(Globals::localPlayer->origin() + Globals::localPlayer->viewOffset(), 
            player->origin() + player->viewOffset());
    TraceFilter filter;
    filter.pSkip = Globals::localPlayer;
                                // solid|opaque|moveable|ignore nodraw
    Interfaces::trace->TraceRay(ray, (0x1 | 0x80 | 0x4000 |    0x2000   ), &filter, &traceToPlayer);
    return (traceToPlayer.m_pEntityHit == player) && !Offsets::lineGoesThroughSmoke(Globals::localPlayer->origin() + Globals::localPlayer->viewOffset(), player->origin() + player->viewOffset(), 1);
}

std::map<int, bool> playersVisible;
void updatePlayersVisible() {
    if (Globals::localPlayer) {
        if (Interfaces::engine->IsInGame()) {
            for (int i = 1; i < Interfaces::globals->maxClients; i++) {
                Player* p = (Player*)Interfaces::entityList->GetClientEntity(i);
                if (p) {
                    if (p->health() > 0 && !p->dormant() && p != Globals::localPlayer && p->team() != Globals::localPlayer->team()) {
                        if (playersVisible.find(i) != playersVisible.end()) {
                            if (!p->dormant() && p->health() > 0) {
                                playersVisible[i] = visCheck(p);
                            }
                        }
                        else {
                            if (!p->dormant() && p->health() > 0) {
                                playersVisible.insert(std::pair<int, bool>(i, visCheck(p)));
                            }
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