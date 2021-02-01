#include "features.hpp"
#include "../../includes.hpp"
#include <sstream>

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

static bool getBox(Entity* entity, int& x, int& y, int& x2, int& y2) {
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

void outlinedText(ImVec2 pos, ImColor color, char* text) {
    Globals::drawList->AddText(ImVec2(pos.x-1, pos.y), ImColor(0, 0, 0, 255), text);
    Globals::drawList->AddText(ImVec2(pos.x+1, pos.y), ImColor(0, 0, 0, 255), text);
    Globals::drawList->AddText(ImVec2(pos.x, pos.y-1), ImColor(0, 0, 0, 255), text);
    Globals::drawList->AddText(ImVec2(pos.x, pos.y+1), ImColor(0, 0, 0, 255), text);
    Globals::drawList->AddText(ImVec2(pos.x, pos.y), color, text);

}

void drawBox(int x, int y, int x2, int y2, bool drawBox, ImColor color, char* rightText, int health = -1) {
    if (drawBox) {
        Globals::drawList->AddRect(ImVec2(x, y), ImVec2(x2, y2), color);
        Globals::drawList->AddRect(ImVec2(x-1, y-1), ImVec2(x2+1, y2+1), ImColor(0, 0, 0, 255));
        Globals::drawList->AddRect(ImVec2(x+1, y+1), ImVec2(x2-1, y2-1), ImColor(0, 0, 0, 255));
    }

    if (health != -1) {
        Globals::drawList->AddRectFilled(ImVec2(x-6, y2-(((float)health/100.f)*(y2-y))-1), 
        ImVec2(x-2, y2+1), ImColor(0, 0, 0, 255));
        Globals::drawList->AddRectFilled(ImVec2(x-5, y2-(((float)health/100.f)*(y2-y))), 
        ImVec2(x-3, y2), ImColor(0, 240, 0, 255));
    }
    
    outlinedText(ImVec2(x2+1, y), ImColor(255, 255, 255, 255), rightText);
}

void drawPlayer(Player* p) {
    if (!p->dormant()) {
        if (p->health() > 0) {
            int x, y, x2, y2;
            if (getBox(p, x, y, x2, y2)) {
                player_info_t info;
                Interfaces::engine->GetPlayerInfo(p->index(), &info);

                if (p->team() != Globals::localPlayer->team()) {
                    std::stringstream rightText;
                    if (CONFIGBOOL("Enemy:Name"))
                        rightText << info.name << "\n";
                    if (CONFIGBOOL("Enemy:Health"))
                        rightText << p->health() << "hp\n";
                    if (CONFIGBOOL("Enemy:Money"))
                        rightText << "$" << p->money() << "\n";
                    
                    drawBox(x, y, x2, y2, CONFIGBOOL("Enemy:Box"), 
                                CONFIGCOL("Enemy:BoxColor"), (char*)rightText.str().c_str(), 
                                CONFIGBOOL("Enemy:HealthBar") ? p->health() : -1);
                }
                if (p->team() == Globals::localPlayer->team()) {
                    std::stringstream rightText;
                    if (CONFIGBOOL("Team:Name"))
                        rightText << info.name << "\n";
                    if (CONFIGBOOL("Team:Health"))
                        rightText << p->health() << "hp\n";
                    if (CONFIGBOOL("Team:Money"))
                        rightText << "$" << p->money() << "\n";
                    
                    drawBox(x, y, x2, y2, CONFIGBOOL("Team:Box"), 
                                CONFIGCOL("Team:BoxColor"), (char*)rightText.str().c_str(), 
                                CONFIGBOOL("Team:HealthBar") ? p->health() : -1);
                }
            }
        }
    }
}

void drawGenericEnt(Entity* ent, bool box, ImColor color, const char* label) {
    int x, y, x2, y2;
    if (getBox(ent, x, y, x2, y2)) {
        drawBox(x, y, x2, y2, box, color, (char*)label, -1);
    }
}

void Features::ESP::drawESP() {
    if (Interfaces::engine->IsInGame()) {
        int highest = Interfaces::entityList->GetHighestEntityIndex();
        for (int i; i < highest; i++) {
            if (Globals::localPlayer) {
                if (i != Interfaces::engine->GetLocalPlayer()) {
                    Entity* ent = (Entity*)Interfaces::entityList->GetClientEntity(i);
                    if (ent) {
                        ClientClass* clientClass = ent->clientClass();

                        /* Player ESP */
                        if (clientClass->m_ClassID == EClassIds::CCSPlayer) {
                            drawPlayer((Player*)ent);
                        }

                        /* Weapon ESP */
                        if ((clientClass->m_ClassID != EClassIds::CBaseWeaponWorldModel && strstr(clientClass->m_pNetworkName, "Weapon")) || clientClass->m_ClassID == EClassIds::CDEagle || clientClass->m_ClassID == EClassIds::CAK47) {
                            if (((Weapon*)ent)->owner() == -1) {
                                try {
                                    drawGenericEnt(ent, CONFIGBOOL("Weapon:Box"), CONFIGCOL("Weapon:BoxColor"), CONFIGBOOL("Weapon:Name") ? itemIndexMap.at(((Weapon*)ent)->itemIndex()) : "");
                                }
                                catch(const std::exception & e) {
                                    Log::log(WARN, "itemDefinitionIndex %d not found!", ((Weapon*)ent)->itemIndex());
                                }
                            }
                        }
                        if (clientClass->m_ClassID == EClassIds::CC4) {
                            if (((Weapon*)ent)->owner() == -1) {
                                drawGenericEnt(ent, CONFIGBOOL("Weapon:Box"), CONFIGCOL("Weapon:BoxColor"), CONFIGBOOL("Weapon:Name") ? "C4" : "");
                            }
                        }

                        /* Planted C4 ESP */
                        if (clientClass->m_ClassID == EClassIds::CPlantedC4) {
                            char label[32] = "";
                            snprintf(label, 32, "Planted C4\n%.3f", ((PlantedC4*)ent)->time() - Interfaces::globals->curtime);
                            drawGenericEnt(ent, CONFIGBOOL("PlantedC4:Box"), CONFIGCOL("PlantedC4:BoxColor"), CONFIGBOOL("PlantedC4:Name") ? label : "");
                        }
                        
                        /* Chicken ESP */
                        if (clientClass->m_ClassID == EClassIds::CChicken) {
                            drawGenericEnt(ent, CONFIGBOOL("Chicken:Box"), CONFIGCOL("Chicken:BoxColor"), CONFIGBOOL("Chicken:Name") ? "Chicken" : "");
                        }

                        /* Fish ESP */
                        if (clientClass->m_ClassID == EClassIds::CFish) {
                            drawGenericEnt(ent, CONFIGBOOL("Fish:Box"), CONFIGCOL("Fish:BoxColor"), CONFIGBOOL("Fish:Name") ? "Fish" : "");
                        }

                        /* Debug ESP Everything*/
                        if (CONFIGBOOL("Debug:EspAll")) {
                            char label[128] = "";
                            snprintf(label, 128, "%d\n%s", clientClass->m_ClassID, clientClass->m_pNetworkName);
                            drawGenericEnt(ent, true, ImColor(255, 255, 255, 255), label);
                        }
                    }
                }
            }
        }
    }
}