#include "../../includes.hpp"

void Menu::drawOverlay(ImDrawList* drawList) {
    drawList->AddText(ImVec2(3, 3), ImColor(255, 255, 255, 255), "gamesneeze-linux");
}