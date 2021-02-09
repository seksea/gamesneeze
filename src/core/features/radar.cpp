#include "features.hpp"

void Features::Radar::espPlayerLoop(Player* p) {
    if (CONFIGBOOL("Visuals>Enemies>ESP>Radar")) {
        if ((Globals::localPlayer->health() == 0 && CONFIGBOOL("Visuals>Enemies>ESP>Only When Dead")) || !CONFIGBOOL("Visuals>Enemies>ESP>Only When Dead")) { 
            if (!p->dormant()) {
                *p->spotted_ptr() = true;
            }
        }
    }
}