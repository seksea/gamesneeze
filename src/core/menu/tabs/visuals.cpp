#include "../menu.hpp"

void Menu::drawVisualsTab() {
    ImGui::Text("Visuals");
    ImGui::BeginChild("Enemies", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.65f, 260), true); {
        ImGui::EndChild();
    }
}