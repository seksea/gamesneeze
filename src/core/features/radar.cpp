#include "features.hpp"

void Features::Radar::espPlayerLoop(Player* p) {
    if (CONFIGBOOL("Visuals>Players>Enemies>Radar")) {
        if ((Globals::localPlayer->health() == 0 && CONFIGBOOL("Visuals>Players>Enemies>Only When Dead")) || !CONFIGBOOL("Visuals>Players>Enemies>Only When Dead")) { 
            if (!p->dormant()) {
                *p->spotted_ptr() = true;
            }
        }
    }
}