#include "../menu.hpp"

void colourPicker(ImVec4* col) {
    float _col[4] {col->x, col->y, col->z, col->w};

    ImGui::ColorEdit4("Box Color", _col, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);

    col->x = _col[0];
    col->y = _col[1];
    col->z = _col[2];
    col->w = _col[3];
}

void Menu::drawVisualsTab() {
    ImGui::Text("Visuals");
    if (ImGui::BeginTabBar("##visTabs", ImGuiTabBarFlags_None)) {
        if (ImGui::BeginTabItem("Enemies")) {
            ImGui::BeginChild("ESP", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.65f, 253), true); {
                ImGui::Text("ESP");
                ImGui::Separator();
                ImGui::Checkbox("Box", &CONFIGBOOL("Enemy:Box"));
                
                ImGui::ColorEdit4("Box Color", (float*)&CONFIGCOL("Enemy:BoxColor"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                Log::log("%f", CONFIGCOL("Enemy:BoxColor").Value.x);
                ImGui::Checkbox("Name", &CONFIGBOOL("Enemy:Name"));
                ImGui::Checkbox("Health", &CONFIGBOOL("Enemy:Health"));
                ImGui::Checkbox("Health Bar", &CONFIGBOOL("Enemy:HealthBar"));
                ImGui::Checkbox("Money", &CONFIGBOOL("Enemy:Money"));
                ImGui::EndChild();
            }
            ImGui::BeginChild("Chams", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.65f, 253), true); {
                ImGui::Text("Chams");
                ImGui::Separator();
                ImGui::EndChild();
            }
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Teammates")) {
            ImGui::BeginChild("ESP", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.65f, 240), true); {
                ImGui::Text("ESP");
                ImGui::Separator();
                ImGui::Checkbox("Box", &CONFIGBOOL("Team:Box"));
                ImGui::Checkbox("Name", &CONFIGBOOL("Team:Name"));
                ImGui::Checkbox("Health", &CONFIGBOOL("Team:Health"));
                ImGui::Checkbox("Health Bar", &CONFIGBOOL("Team:HealthBar"));
                ImGui::Checkbox("Money", &CONFIGBOOL("Team:Money"));
                ImGui::EndChild();
            }
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("World")) {
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }
}