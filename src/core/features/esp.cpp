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

void drawBox(int x, int y, int x2, int y2, bool drawBox, ImColor color, char* topText, char* rightText, int health = -1, bool dynamicHealthColor = false, ImColor defaultHealthBarColor = ImColor(0, 240, 0, 255)) {
    if (drawBox) {
        Globals::drawList->AddRect(ImVec2(x, y), ImVec2(x2, y2), color);
        Globals::drawList->AddRect(ImVec2(x-1, y-1), ImVec2(x2+1, y2+1), ImColor(0, 0, 0, 255));
        Globals::drawList->AddRect(ImVec2(x+1, y+1), ImVec2(x2-1, y2-1), ImColor(0, 0, 0, 255));
    }

    if (health != -1) {
        //border color
        Globals::drawList->AddRectFilled(ImVec2(x - 6, y2 - (((float) health / 100.f) * (y2 - y)) - 1),
                                         ImVec2(x - 2, y2 + 1), ImColor(0, 0, 0, 255));
        //bar color
        ImColor healthBarColor = defaultHealthBarColor;
        if (dynamicHealthColor) {
            ImGui::ColorConvertHSVtoRGB(((float)health-20.f)/255.f, 1.f, 1.f, healthBarColor.Value.x, healthBarColor.Value.y, healthBarColor.Value.z);
        }
        Globals::drawList->AddRectFilled(ImVec2(x - 5, y2 - (((float) health / 100.f) * (y2 - y))),ImVec2(x - 3, y2), healthBarColor);
    }
    outlinedText(ImVec2(x2+1, y), ImColor(255, 255, 255, 255), rightText);
    outlinedText(ImVec2(x+((x2-x)/2)-(ImGui::CalcTextSize(topText).x/2), y-(ImGui::CalcTextSize(topText).y)), ImColor(255, 255, 255, 255), topText);
}

void drawSkeleton(Player* p, ImColor color) {
    studiohdr_t* model = Interfaces::modelInfo->GetStudioModel(p->model());
    if (model) {
        matrix3x4_t boneMatrix[128];
        if (p->getHitboxBones(boneMatrix)) {
            for (int i = 0; i < model->numbones; i++) {
                mstudiobone_t* bone = model->pBone(i);
                if (bone && (bone->flags & BONE_USED_BY_HITBOX) && bone->parent != -1) {
                    Vector screenBonePos, screenParentBonePos;
                    if (worldToScreen(Vector(boneMatrix[i][0][3], boneMatrix[i][1][3], boneMatrix[i][2][3]), screenBonePos) &&
                        worldToScreen(Vector(boneMatrix[bone->parent][0][3], boneMatrix[bone->parent][1][3], boneMatrix[bone->parent][2][3]), screenParentBonePos)) {
                        Globals::drawList->AddLine(ImVec2{screenBonePos.x, screenBonePos.y}, ImVec2{screenParentBonePos.x, screenParentBonePos.y}, color);
                    }
                }
            }
        }
    }
}

void drawForwardTrack(Player* p) {
    matrix3x4_t boneMatrix[128];
    if (p->getAnythingBones(boneMatrix)) {
        Vector targetEyePos = Vector(boneMatrix[8][0][3], boneMatrix[8][1][3], boneMatrix[8][2][3]); // 8 is headbone in bonematrix
        targetEyePos+=(p->velocity()/64)*3;
        Vector screenFtrackPos;
        if (worldToScreen(targetEyePos, screenFtrackPos)) {
            Globals::drawList->AddCircleFilled(ImVec2(screenFtrackPos.x, screenFtrackPos.y), 3, ImColor(0, 0, 0, 100));
            Globals::drawList->AddCircleFilled(ImVec2(screenFtrackPos.x, screenFtrackPos.y), 3, ImColor(200, 200, 200, 100));
        }
    }
}

void drawPlayer(Player* p) {
    if (!p->dormant()) {
        if (p->health() > 0) {
            int x, y, x2, y2;
            if (getBox(p, x, y, x2, y2)) {
                player_info_t info;
                Interfaces::engine->GetPlayerInfo(p->index(), &info);

                if (p->team() != Globals::localPlayer->team()) {
                    
                    if (CONFIGBOOL("Visuals>Players>Enemies>Vis Check") ? (Globals::localPlayer->health() > 0 ? p->visible() : true) : true) {
                        if (CONFIGBOOL("Visuals>Players>Enemies>Only When Dead") ? (Globals::localPlayer->health() == 0) : true) {
                            std::stringstream rightText;
                            if (CONFIGBOOL("Visuals>Players>Enemies>Health"))
                                rightText << p->health() << "hp\n";
                            if (CONFIGBOOL("Visuals>Players>Enemies>Money"))
                                rightText << "$" << p->money() << "\n";
                            
                            drawBox(x, y, x2, y2, CONFIGBOOL("Visuals>Players>Enemies>Box"), 
                                        CONFIGCOL("Visuals>Players>Enemies>Box Color"), CONFIGBOOL("Visuals>Players>Enemies>Name") ? info.name : (char*)"", 
                                        (char*)rightText.str().c_str(), CONFIGBOOL("Visuals>Players>Enemies>Health Bar") ? p->health() : -1, CONFIGBOOL("Visuals>Players>Enemies>Dynamic Color"), 
                                        CONFIGCOL("Visuals>Players>Enemies>Health Bar Color"));
                            
                            if (CONFIGBOOL("Visuals>Players>Enemies>Skeleton"))
                                drawSkeleton(p, CONFIGCOL("Visuals>Players>Enemies>Skeleton Color"));

                            if (CONFIGBOOL("Visuals>Players>Enemies>Forwardtrack Dots"))
                                drawForwardTrack(p);
                        }
                    }
                }
                if (p->team() == Globals::localPlayer->team()) {
                    if ((Globals::localPlayer->health() == 0 && CONFIGBOOL("Visuals>Players>Teammates>Only When Dead")) || !CONFIGBOOL("Visuals>Players>Teammates>Only When Dead")) {
                        std::stringstream rightText;
                        if (CONFIGBOOL("Visuals>Players>Teammates>Health"))
                            rightText << p->health() << "hp\n";
                        if (CONFIGBOOL("Visuals>Players>Teammates>Money"))
                            rightText << "$" << p->money() << "\n";
                        
                        drawBox(x, y, x2, y2, CONFIGBOOL("Visuals>Players>Teammates>Box"), 
                                    CONFIGCOL("Visuals>Players>Teammates>Box Color"), CONFIGBOOL("Visuals>Players>Teammates>Name") ? info.name : (char*)"", 
                                    (char*)rightText.str().c_str(), CONFIGBOOL("Visuals>Players>Teammates>Health Bar") ? p->health() : -1, CONFIGBOOL("Visuals>Players>Teammates>Dynamic Color"), 
                                    CONFIGCOL("Visuals>Players>Teammates>Health Bar Color"));

                        if (CONFIGBOOL("Visuals>Players>Teammates>Skeleton"))
                            drawSkeleton(p, CONFIGCOL("Visuals>Players>Teammates>Skeleton Color"));
                    }
                }
            }
        }
    }
}

void drawGenericEnt(Entity* ent, bool box, ImColor color, const char* label) {
    int x, y, x2, y2;
    if (getBox(ent, x, y, x2, y2)) {
        drawBox(x, y, x2, y2, box, color, (char*)label, (char*)"", -1);
    }
}

void Features::ESP::draw() {
    if (Interfaces::engine->IsInGame()) {
        for (auto i : entityDistanceMap) {
            if (Globals::localPlayer) {
                if (i.second != Interfaces::engine->GetLocalPlayer()) {
                    Entity* ent = (Entity*)Interfaces::entityList->GetClientEntity(i.second);
                    if (ent) {
                        ClientClass* clientClass = ent->clientClass();

                        /* Player ESP */
                        if (clientClass->m_ClassID == EClassIds::CCSPlayer) {
                            drawPlayer((Player*)ent);
                            Features::Radar::espPlayerLoop((Player*)ent);
                        }

                        /* Weapon ESP */
                        if ((clientClass->m_ClassID != EClassIds::CBaseWeaponWorldModel && strstr(clientClass->m_pNetworkName, "Weapon")) || clientClass->m_ClassID == EClassIds::CDEagle || clientClass->m_ClassID == EClassIds::CC4 || clientClass->m_ClassID == EClassIds::CAK47) {
                            if (((Weapon*)ent)->owner() == -1) {
                                try {
                                    drawGenericEnt(ent, CONFIGBOOL("Visuals>World>Items>Weapon Box"), CONFIGCOL("Visuals>World>Items>Weapon Box Color"), CONFIGBOOL("Visuals>World>Items>Weapon Label") ? itemIndexMap.at(((Weapon*)ent)->itemIndex()) : "");
                                }
                                catch(const std::exception & e) {
                                    //Log::log(WARN, "itemDefinitionIndex %d not found!", ((Weapon*)ent)->itemIndex());
                                }
                            }
                        }

                        /* Planted C4 ESP */
                        if (clientClass->m_ClassID == EClassIds::CPlantedC4) {
                            char label[32] = "";
                            snprintf(label, 32, "Planted C4\n%.3f", ((PlantedC4*)ent)->time() - Interfaces::globals->curtime);
                            drawGenericEnt(ent, CONFIGBOOL("Visuals>World>Items>Planted C4 Box"), CONFIGCOL("Visuals>World>Items>Planted C4 Box Color"), CONFIGBOOL("Visuals>World>Items>Planted C4 Label") ? label : "");
                            AutoDefuse::onBombRender((PlantedC4*)ent);
                        }
                        
                        if (clientClass->m_ClassID == EClassIds::CEnvTonemapController) {
                            Nightmode::onTonemapController((TonemapController*)ent);
                        }

                        /* Chicken ESP */
                        if (clientClass->m_ClassID == EClassIds::CChicken) {
                            drawGenericEnt(ent, CONFIGBOOL("Visuals>World>Items>Chicken Box"), CONFIGCOL("Visuals>World>Items>Chicken Box Color"), CONFIGBOOL("Visuals>World>Items>Chicken Label") ? "Chicken" : "");
                        }

                        /* Fish ESP */
                        if (clientClass->m_ClassID == EClassIds::CFish) {
                            drawGenericEnt(ent, CONFIGBOOL("Visuals>World>Items>Fish Box"), CONFIGCOL("Visuals>World>Items>Fish Box Color"), CONFIGBOOL("Visuals>World>Items>Fish Label") ? "Fish" : "");
                        }

                        /* Debug ESP Everything*/
                        if (CONFIGBOOL("Visuals>World>Items>ESP Quite literally everything")) {
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