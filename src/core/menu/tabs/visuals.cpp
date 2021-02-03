#include "../menu.hpp"

const char* chamsMaterials[] = {"None", "Shaded", "Flat", "Screen Pulse", "Energy Ball"};

void Menu::drawVisualsTab() {
    ImGui::Text("Visuals");
    if (ImGui::BeginTabBar("##visTabs", ImGuiTabBarFlags_None)) {
        if (ImGui::BeginTabItem("Enemies")) {
            ImGui::BeginChild("ESP", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.65f, 253), true); {
                ImGui::Text("ESP");
                ImGui::Separator();
                ImGui::Checkbox("Box", &CONFIGBOOL("Enemy:Box"));
                ImGui::ColorEdit4("Box Color", (float*)&CONFIGCOL("Enemy:BoxColor"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                ImGui::Checkbox("Name", &CONFIGBOOL("Enemy:Name"));
                ImGui::Checkbox("Health", &CONFIGBOOL("Enemy:Health"));
                ImGui::Checkbox("Health Bar", &CONFIGBOOL("Enemy:HealthBar"));
                ImGui::Checkbox("Money", &CONFIGBOOL("Enemy:Money"));
                ImGui::EndChild();
            }
            ImGui::BeginChild("Chams", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.65f, 253), true); {
                ImGui::Text("Chams");
                ImGui::Separator();
                ImGui::Text("Visible");
                ImGui::Combo("##VisMaterial", &CONFIGINT("Enemy:ChamsMaterial"), chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
                ImGui::SameLine();
                ImGui::ColorEdit4("Chams Primary Color", (float*)&CONFIGCOL("Enemy:ChamsPrimaryColor"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                
                ImGui::Text("Ignore Z");
                ImGui::Combo("##IZMaterial", &CONFIGINT("Enemy:IgnoreZChamsMaterial"), chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
                ImGui::SameLine();
                ImGui::ColorEdit4("IgnoreZ Chams Primary Color", (float*)&CONFIGCOL("Enemy:IgnoreZChamsPrimaryColor"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                ImGui::EndChild();
            }
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Teammates")) {
            ImGui::BeginChild("ESP", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.65f, 253), true); {
                ImGui::Text("ESP");
                ImGui::Separator();
                ImGui::Checkbox("Box", &CONFIGBOOL("Team:Box"));
                ImGui::ColorEdit4("Box Color", (float*)&CONFIGCOL("Team:BoxColor"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                ImGui::Checkbox("Name", &CONFIGBOOL("Team:Name"));
                ImGui::Checkbox("Health", &CONFIGBOOL("Team:Health"));
                ImGui::Checkbox("Health Bar", &CONFIGBOOL("Team:HealthBar"));
                ImGui::Checkbox("Money", &CONFIGBOOL("Team:Money"));
                ImGui::EndChild();
            }
            ImGui::BeginChild("Chams", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.65f, 253), true); {
                ImGui::Text("Chams");
                ImGui::Separator();
                ImGui::Text("Visible");
                ImGui::Combo("##VisMaterial", &CONFIGINT("Team:ChamsMaterial"), chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
                ImGui::SameLine();
                ImGui::ColorEdit4("Chams Primary Color", (float*)&CONFIGCOL("Team:ChamsPrimaryColor"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                
                ImGui::Text("Ignore Z");
                ImGui::Combo("##IZMaterial", &CONFIGINT("Team:IgnoreZChamsMaterial"), chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
                ImGui::SameLine();
                ImGui::ColorEdit4("IgnoreZ Chams Primary Color", (float*)&CONFIGCOL("Team:IgnoreZChamsPrimaryColor"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                ImGui::EndChild();
            }
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("World")) {
            ImGui::BeginChild("Local Player", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.65f, 253), true); {
                ImGui::Text("Local Player");
                ImGui::Separator();
                ImGui::Text("Arm Chams");
                ImGui::Combo("##ArmMaterial", &CONFIGINT("Arms:ChamsMaterial"), chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
                ImGui::SameLine();
                ImGui::ColorEdit4("Arm Chams Primary Color", (float*)&CONFIGCOL("Arms:ChamsPrimaryColor"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);

                ImGui::Text("Weapon Chams");
                ImGui::Combo("##WeaponMaterial", &CONFIGINT("Weapon:ChamsMaterial"), chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
                ImGui::SameLine();
                ImGui::ColorEdit4("Weapon Chams Primary Color", (float*)&CONFIGCOL("Weapon:ChamsPrimaryColor"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);

                ImGui::Checkbox("Recoil Crosshair", &CONFIGBOOL("World:SpreadCrosshair"));
                ImGui::EndChild();
            }
            ImGui::SameLine();
            ImGui::BeginChild("Items", ImVec2(0, 253), true); {
                ImGui::Text("Items");
                ImGui::Separator();
                ImGui::Checkbox("Weapon Box", &CONFIGBOOL("Weapon:Box"));
                ImGui::ColorEdit4("Weapon Box Color", (float*)&CONFIGCOL("Weapon:BoxColor"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                ImGui::Checkbox("Weapon Label", &CONFIGBOOL("Weapon:Name"));
                ImGui::Separator();

                ImGui::Checkbox("Planted C4 Box", &CONFIGBOOL("PlantedC4:Box"));
                ImGui::ColorEdit4("Planted C4 Box Color", (float*)&CONFIGCOL("PlantedC4:BoxColor"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                ImGui::Checkbox("Planted C4 Label", &CONFIGBOOL("PlantedC4:Name"));
                ImGui::Separator();
                
                ImGui::Checkbox("Chicken Box", &CONFIGBOOL("Chicken:Box"));
                ImGui::ColorEdit4("Chicken Box Color", (float*)&CONFIGCOL("Chicken:BoxColor"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                ImGui::Checkbox("Chicken Label", &CONFIGBOOL("Chicken:Name"));
                ImGui::Separator();
                
                ImGui::Checkbox("Fish Box", &CONFIGBOOL("Fish:Box"));
                ImGui::ColorEdit4("Fish Box Color", (float*)&CONFIGCOL("Fish:BoxColor"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                ImGui::Checkbox("Fish Label", &CONFIGBOOL("Fish:Name"));
                ImGui::Separator();

                ImGui::Checkbox("ESP Quite literally everything", &CONFIGBOOL("Debug:EspAll"));
                ImGui::EndChild();
            }
            ImGui::BeginChild("World", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.65f, 253), true); {
                ImGui::Text("World");
                ImGui::Separator();
                if (
                  ImGui::ColorEdit4("World Colour Modulation", (float*)&CONFIGCOL("World:WorldColorModulation"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel) || 
                  ImGui::Button("Update Colour Modulation")) {
                    Features::WorldColorModulate::updateColorModulation();
                }

                ImGui::EndChild();
            }
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }
}