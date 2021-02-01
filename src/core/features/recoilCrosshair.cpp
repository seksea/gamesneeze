#include "features.hpp"
#include "../../includes.hpp"

void Features::RecoilCrosshair::drawCrosshair() {
    if (CONFIGBOOL("World:SpreadCrosshair")) {
        if (Globals::localPlayer) {
            if (Interfaces::engine->IsInGame()) {
                if (Globals::localPlayer->health() > 0) {
                    QAngle punchAngle = Globals::localPlayer->aimPunch();

                    int x = Globals::screenSizeX / 2;
                    int y = Globals::screenSizeY / 2;
                    int dx = Globals::screenSizeX / 90; // swap 90 with fov in future
                    int dy = Globals::screenSizeY / 90; // swap 90 with fov in future

                    int crosshairX = (int) (x - (dx * punchAngle.y ) );
                    int crosshairY = (int) (y + (dy * punchAngle.x ) );

                
                    Globals::drawList->AddRectFilled(ImVec2(crosshairX - 4, crosshairY - 1), ImVec2(crosshairX + 5, crosshairY + 2), ImColor( 0, 0, 0, 225 ) );
                    Globals::drawList->AddRectFilled(ImVec2(crosshairX - 1, crosshairY - 4), ImVec2(crosshairX + 2, crosshairY + 5), ImColor( 0, 0, 0, 225 ) );
                    Globals::drawList->AddLine(ImVec2(crosshairX - 3, crosshairY), ImVec2(crosshairX + 4, crosshairY), ImColor( 255, 255, 255, 255 ) );
                    Globals::drawList->AddLine(ImVec2(crosshairX, crosshairY + 3), ImVec2(crosshairX, crosshairY - 4), ImColor( 255, 255, 255, 255 ) );
                }
            }
        }
    }
}