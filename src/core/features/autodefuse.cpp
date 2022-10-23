#include "features.hpp"
void Features::AutoDefuse::onBombRender(PlantedC4* bomb) {
    if (CONFIGBOOL("Misc>Misc>Misc>Auto Defuse") && getDistanceNoSqrt(Globals::localPlayer->origin(), bomb->origin()) < 5625) { // Could also check whether you're looking at the bomb but distance check should be good enough
        float timeRemaining = bomb->time() - (Interfaces::globals->curtime + ((float)playerResource->GetPing(Globals::localPlayer->index())/1000.f));
        if (CONFIGBOOL("Misc>Misc>Misc>Latest Defuse") ? 
            timeRemaining < (Globals::localPlayer->defuser() ? 5.1f: 10.1f) : true) {
            shouldDefuse = true;
            return;
        }
    }
    shouldDefuse = false;
}