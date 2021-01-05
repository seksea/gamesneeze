#include "../../includes.hpp"

float framerate;
void Menu::drawOverlay(ImDrawList* drawList) {
    framerate = 0.9 * framerate + ( 0.1 ) * Interfaces::globals->absoluteframetime;
    drawList->AddText(ImVec2(3, 3), ImColor(255, 255, 255, 255), (std::string("gamesneeze-linux fps:") + std::to_string((int)(1.f/framerate))).c_str());
}