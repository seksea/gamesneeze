#include "features.hpp"
// Hitmarkers are triggered in hooks/events.cpp

void Features::Hitmarkers::draw() {
    if (Interfaces::engine->IsInGame()) {
        if (CONFIGBOOL("Misc>Misc>Hitmarkers>Hitmarkers")) {
            if (Interfaces::globals->curtime < drawHitmarkerTill) {
                ImColor col = ImColor(255, 255, 255, 255);
                col.Value.w = (Interfaces::globals->curtime < drawHitmarkerTill-0.2) ? 1.f : 0 + ((drawHitmarkerTill-Interfaces::globals->curtime)*6);
                Globals::drawList->AddLine(ImVec2((Globals::screenSizeX/2) - 8, (Globals::screenSizeY/2) - 8), ImVec2((Globals::screenSizeX/2) - 4, (Globals::screenSizeY/2) - 4), col);
                Globals::drawList->AddLine(ImVec2((Globals::screenSizeX/2) + 8, (Globals::screenSizeY/2) - 8), ImVec2((Globals::screenSizeX/2) + 4, (Globals::screenSizeY/2) - 4), col);
                Globals::drawList->AddLine(ImVec2((Globals::screenSizeX/2) - 8, (Globals::screenSizeY/2) + 8), ImVec2((Globals::screenSizeX/2) - 4, (Globals::screenSizeY/2) + 4), col);
                Globals::drawList->AddLine(ImVec2((Globals::screenSizeX/2) + 8, (Globals::screenSizeY/2) + 8), ImVec2((Globals::screenSizeX/2) + 4, (Globals::screenSizeY/2) + 4), col);
            }
            else if (Interfaces::globals->curtime-10 < drawHitmarkerTill) {
                drawHitmarkerTill = 0; // If its more than 10 secs in future, its probably too far to keep drawing and something has gone wrong, so set it to 0
            }
        }
    }
}