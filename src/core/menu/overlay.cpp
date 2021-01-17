#include "../../includes.hpp"

float framerate;
void Menu::drawOverlay(ImDrawList* drawList) {
    framerate = 0.9 * framerate + ( 0.1 ) * Interfaces::globals->absoluteframetime;
    char watermarkText[64]; 
    sprintf(watermarkText, "gamesneeze-linux fps: %d", (int)(1.f/framerate));
    // Hacky way to do black outline
    drawList->AddText(ImVec2(4, 2), ImColor(0, 0, 0, 255), watermarkText);
    drawList->AddText(ImVec2(3, 2), ImColor(0, 0, 0, 255), watermarkText);
    drawList->AddText(ImVec2(2, 2), ImColor(0, 0, 0, 255), watermarkText);
    drawList->AddText(ImVec2(4, 3), ImColor(0, 0, 0, 255), watermarkText);
    //drawList->AddText(ImVec2(3, 3), ImColor(255, 255, 255, 255), watermarkText);
    drawList->AddText(ImVec2(2, 3), ImColor(0, 0, 0, 255), watermarkText);
    drawList->AddText(ImVec2(4, 4), ImColor(0, 0, 0, 255), watermarkText);
    drawList->AddText(ImVec2(3, 4), ImColor(0, 0, 0, 255), watermarkText);
    drawList->AddText(ImVec2(2, 4), ImColor(0, 0, 0, 255), watermarkText);
    drawList->AddText(ImVec2(3, 3), ImColor(255, 255, 255, 255), watermarkText);
}