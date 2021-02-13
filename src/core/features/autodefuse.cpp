#include "features.hpp"

float getDistance(Vector pos1, Vector pos2) {
    //Do 3d pythag
    float a = abs(pos1.x-pos2.x);
    float b = abs(pos1.y-pos2.y);
    float c = abs(pos1.z-pos2.z);
    return sqrt(pow(a, 2.f) + pow(b, 2.f) + pow(c, 2.f));
}

void Features::AutoDefuse::onBombRender(PlantedC4* bomb) {
    if (CONFIGBOOL("Misc>Misc>Misc>Auto Defuse")) {
        // Could also check whether you're looking at the bomb but distance check should be good enough
        if (getDistance(Globals::localPlayer->origin(), bomb->origin()) < 75) {
            float timeRemaining = bomb->time() - Interfaces::globals->curtime;
            if (CONFIGBOOL("Misc>Misc>Misc>Latest Defuse") ? 
                timeRemaining < (Globals::localPlayer->defuser() ? 5.1f: 10.1f) : true) { // TODO: Account for ping
                shouldDefuse = true;
            }
            else {
                shouldDefuse = false;
            }
        }
        else {
            shouldDefuse = false;
        }
    }
    else {
        shouldDefuse = false;
    }
}