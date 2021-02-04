#include "features.hpp"
#include "../../includes.hpp"

void Features::RecoilCrosshair::draw() {
    if (CONFIGBOOL("World:SpreadCrosshair")) {
        if (Globals::localPlayer) {
            if (Interfaces::engine->IsInGame()) {
                if (Globals::localPlayer->health() > 0) {
                    if (Globals::localPlayer->activeWeapon()) {
                        Weapon* weapon = (Weapon*)Interfaces::entityList->GetClientEntity((uintptr_t)Globals::localPlayer->activeWeapon() & 0xFFF); // GetClientEntityFromHandle is being gay
                        
                        if (weapon) {
                            float rad = ((weapon->GetSpread()+weapon->GetInaccuracy())*Globals::screenSizeY)/1.5f;

                            int x = Globals::screenSizeX / 2;
                            int y = Globals::screenSizeY / 2;
                            int dx = Globals::screenSizeX / 90; // swap 90 with fov in future
                            int dy = Globals::screenSizeY / 90; // swap 90 with fov in future

                            QAngle punchAngle = Globals::localPlayer->aimPunch();
                            int crosshairX = (int) (x - (dx * punchAngle.y ) );
                            int crosshairY = (int) (y + (dy * punchAngle.x ) );

                            Globals::drawList->AddCircleFilled(ImVec2(crosshairX, crosshairY), rad, CONFIGCOL("World:SpreadCrosshairColor"));
                            Globals::drawList->AddCircle(ImVec2(crosshairX, crosshairY), rad, CONFIGCOL("World:SpreadCrosshairBorderColor"));
                        }
                    }
                }
            }
        }
    }
}