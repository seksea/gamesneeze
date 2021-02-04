#include "features.hpp"
#include "../../includes.hpp"

void Features::RecoilCrosshair::draw() {
    int crosshairX;
    int crosshairY;
    if (CONFIGBOOL("World:SpreadCrosshair") || CONFIGBOOL("World:RecoilCrosshair") ) {
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
                                if (CONFIGBOOL("World:RecoilCrosshair")) {
                                    rad = 5;
                                    crosshairX = (int) (x - (dx * punchAngle.y));
                                    crosshairY = (int) (y + (dy * punchAngle.x));
                                }
                                if (CONFIGBOOL("World:SpreadCrosshair")) {
                                    if(!CONFIGBOOL("World:RecoilCrosshair")) {
                                        punchAngle.y = 0;
                                        punchAngle.x = 0;
                                    }
                                    rad = ((weapon->GetSpread() + weapon->GetInaccuracy()) * Globals::screenSizeY) / 1.5f;
                                    crosshairX = x - (dx * punchAngle.y);
                                    crosshairY = y + (dx * punchAngle.x);
                                }

                            //drawing
                            Globals::drawList->AddCircleFilled(ImVec2(crosshairX, crosshairY), rad, CONFIGCOL("World:SpreadCrosshairColor"));
                            Globals::drawList->AddCircle(ImVec2(crosshairX, crosshairY), rad, CONFIGCOL("World:SpreadCrosshairBorderColor"));
                        }
                    }
                }
            }
        }
    }
}