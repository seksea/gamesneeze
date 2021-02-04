#include "../../includes.hpp"

float framerate;
void Menu::drawOverlay(ImDrawList* drawList) {
    Globals::drawList = drawList;
    framerate = 0.9 * framerate + ( 0.1 ) * Interfaces::globals->absoluteframetime;
    char watermarkText[64]; 
    sprintf(watermarkText, "gamesneeze-linux fps: %d", (int)(1.f/framerate));
    // Hacky way to do black shadow but it works
    Globals::drawList->AddText(ImVec2(4, 4), ImColor(0, 0, 0, 255), watermarkText);
    Globals::drawList->AddText(ImVec2(3, 3), ImColor(255, 255, 255, 255), watermarkText);

    Features::ESP::draw();
    Features::RecoilCrosshair::draw();
    Features::Spectators::draw();
}