#include "features.hpp"
#include "../../includes.hpp"

void Features::RecoilCrosshair::draw() {
    if (CONFIGBOOL("Visuals>World>Local Player>Spread Crosshair") || CONFIGBOOL("Visuals>World>Local Player>Recoil Crosshair") ) {
        if (Globals::localPlayer) {
            if (Interfaces::engine->IsInGame()) {
                if (Globals::localPlayer->health() > 0) {
                    if (Globals::localPlayer->activeWeapon()) {
                        Weapon* weapon = (Weapon*)Interfaces::entityList->GetClientEntity((uintptr_t)Globals::localPlayer->activeWeapon() & 0xFFF); // GetClientEntityFromHandle is being gay
                        if (weapon) {
                            float rad;
                            int x = Globals::screenSizeX / 2;
                            int y = Globals::screenSizeY / 2;
                            int dx = Globals::screenSizeX / 90; // swap 90 with fov in future
                            int dy = Globals::screenSizeY / 90; // swap 90 with fov in future
                            QAngle punchAngle = Globals::localPlayer->aimPunch();
                            if (CONFIGBOOL("Visuals>World>Local Player>Recoil Crosshair")) {
                                rad = 5;
                                x = (int)(x - (dx * punchAngle.y));
                                y = (int)(y + (dy * punchAngle.x));
                            }
                            if (CONFIGBOOL("Visuals>World>Local Player>Spread Crosshair")) {
                                rad = ((weapon->GetSpread() + weapon->GetInaccuracy()) * Globals::screenSizeY) / 1.5f;
                            }

                            //drawing
                            Globals::drawList->AddCircleFilled(ImVec2(x, y), rad, CONFIGCOL("Visuals>World>Local Player>Crosshair Color"));
                            Globals::drawList->AddCircle(ImVec2(x, y), rad, CONFIGCOL("Visuals>World>Local Player>Crosshair Border Color"));
                        }
                    }
                }
            }
        }
    }
}