#include "features.hpp"
#include "../../includes.hpp"

bool worldToScreen( const Vector& origin, Vector& screen ) {
	float w = Globals::worldToScreenMatrix[3][0] * origin.x
			  + Globals::worldToScreenMatrix[3][1] * origin.y
			  + Globals::worldToScreenMatrix[3][2] * origin.z
			  + Globals::worldToScreenMatrix[3][3];

	if ( w < 0.01f )
		return false;

	float inverseW = 1 / w;

	screen.x = (Globals::screenSizeX/2) + (0.5f * ((Globals::worldToScreenMatrix[0][0] * origin.x + Globals::worldToScreenMatrix[0][1] * origin.y +
						  			 Globals::worldToScreenMatrix[0][2] * origin.z + Globals::worldToScreenMatrix[0][3]) * inverseW) * Globals::screenSizeX + 0.5f);

	screen.y = (Globals::screenSizeY/2) - (0.5f * ((Globals::worldToScreenMatrix[1][0] * origin.x + Globals::worldToScreenMatrix[1][1] * origin.y +
									  Globals::worldToScreenMatrix[1][2] * origin.z + Globals::worldToScreenMatrix[1][3]) * inverseW) * Globals::screenSizeY + 0.5f);
	return true;
}

static bool getBox(player* entity, int& x, int& y, int& x2, int& y2) {
	Vector vOrigin, min, max;
	Vector flb, brt, blb, frt, frb, brb, blt, flt; // think of these as Front-Left-Bottom/Front-Left-Top... Etc.

	vOrigin = entity->origin();
	min = entity->collideable().OBBMins() + vOrigin;
	max = entity->collideable().OBBMaxs() + vOrigin;

	Vector points[] = { Vector( min.x, min.y, min.z ),
						Vector( min.x, max.y, min.z ),
						Vector( max.x, max.y, min.z ),
						Vector( max.x, min.y, min.z ),
						Vector( max.x, max.y, max.z ),
						Vector( min.x, max.y, max.z ),
						Vector( min.x, min.y, max.z ),
						Vector( max.x, min.y, max.z ) };

	// Get screen positions
	if ( !worldToScreen( points[3], flb ) || !worldToScreen( points[5], brt )
		 || !worldToScreen( points[0], blb ) || !worldToScreen( points[4], frt )
		 || !worldToScreen( points[2], frb ) || !worldToScreen( points[1], brb )
		 || !worldToScreen( points[6], blt ) || !worldToScreen( points[7], flt ) )
		return false;

	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	float left = flb.x;
	float top = flb.y;
	float right = flb.x;
	float bottom = flb.y;

	for ( int i = 1; i < 8; i++ ) {
		if (left > arr[i].x)
			left = arr[i].x;
		if (bottom < arr[i].y)
			bottom = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (top > arr[i].y)
			top = arr[i].y;
	}

	x = (int)left;
	y = (int)top;
	x2 = (int)right;
	y2 = (int)bottom;

	return true;
}

void drawPlayerBox(player* p) {
    int x, y, x2, y2;
    if (getBox(p, x, y, x2, y2)) {
        player_info_t info;
        Interfaces::engine->GetPlayerInfo(p->index(), &info);
        Globals::drawList->AddRect(ImVec2(x, y), ImVec2(x2, y2), ImColor(255, 255, 255, 255));
        Globals::drawList->AddRect(ImVec2(x-1, y-1), ImVec2(x2+1, y2+1), ImColor(0, 0, 0, 255));
        Globals::drawList->AddRect(ImVec2(x+1, y+1), ImVec2(x2-1, y2-1), ImColor(0, 0, 0, 255));

        Globals::drawList->AddRectFilled(ImVec2(x-6, y2-(((float)p->health()/100.f)*(y2-y))-1), 
        ImVec2(x-2, y2+1), ImColor(0, 0, 0, 255));
        Globals::drawList->AddRectFilled(ImVec2(x-5, y2-(((float)p->health()/100.f)*(y2-y))), 
        ImVec2(x-3, y2), ImColor(0, 240, 0, 255));
        
        Globals::drawList->AddText(ImVec2(x2, y), ImColor(0, 0, 0, 255), info.name);
        Globals::drawList->AddText(ImVec2(x2+2, y), ImColor(0, 0, 0, 255), info.name);
        Globals::drawList->AddText(ImVec2(x2+1, y-1), ImColor(0, 0, 0, 255), info.name);
        Globals::drawList->AddText(ImVec2(x2+1, y+1), ImColor(0, 0, 0, 255), info.name);
        Globals::drawList->AddText(ImVec2(x2+1, y), ImColor(255, 255, 255, 255), info.name);

        char hpText[16];
        sprintf(hpText, "%d hp", p->health());

        Globals::drawList->AddText(ImVec2(x2, y+16), ImColor(0, 0, 0, 255), hpText);
        Globals::drawList->AddText(ImVec2(x2+2, y+16), ImColor(0, 0, 0, 255), hpText);
        Globals::drawList->AddText(ImVec2(x2+1, y+15), ImColor(0, 0, 0, 255), hpText);
        Globals::drawList->AddText(ImVec2(x2+1, y+17), ImColor(0, 0, 0, 255), hpText);
        Globals::drawList->AddText(ImVec2(x2+1, y+16), ImColor(255, 255, 255, 255), hpText);

        char moneyText[16];
        sprintf(moneyText, "$%d", p->money());

        Globals::drawList->AddText(ImVec2(x2, y+32), ImColor(0, 0, 0, 255), moneyText);
        Globals::drawList->AddText(ImVec2(x2+2, y+32), ImColor(0, 0, 0, 255), moneyText);
        Globals::drawList->AddText(ImVec2(x2+1, y+31), ImColor(0, 0, 0, 255), moneyText);
        Globals::drawList->AddText(ImVec2(x2+1, y+33), ImColor(0, 0, 0, 255), moneyText);
        Globals::drawList->AddText(ImVec2(x2+1, y+32), ImColor(30, 160, 30, 255), moneyText);
    }
}

void Features::ESP::drawESP() {
    if (Menu::ESPBox) {
        if (Interfaces::engine->IsInGame()) {
            for (int i; i < 64; i++) {
                if (i != Interfaces::engine->GetLocalPlayer()) {
                    player* p = (player*)Interfaces::entityList->GetClientEntity(i);
                    if (p) {
                        if (!p->dormant()) {
                            if (p->health() > 0) {
                                drawPlayerBox(p);
                            }
                        }
                    }
                }
            }
        }
    }
}