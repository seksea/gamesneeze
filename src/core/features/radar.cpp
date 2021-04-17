#include "features.hpp"

void Features::Radar::espPlayerLoop(Player* p) {
    if (!p->dormant() && CONFIGBOOL("Visuals>Players>Enemies>Radar") && ((Globals::localPlayer->health() == 0 && CONFIGBOOL("Visuals>Players>Enemies>Only When Dead")) || !CONFIGBOOL("Visuals>Players>Enemies>Only When Dead"))) { 
        *p->spotted_ptr() = true;
    }
}