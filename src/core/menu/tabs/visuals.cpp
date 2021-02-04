#include "../menu.hpp"

const char* chamsMaterials[] = {"None", "Shaded", "Flat", "Screen Pulse", "Energy Ball", "Glow", "Plastic", "Darude"};

void Menu::drawVisualsTab() {
    ImGui::Text("Visuals");
    if (ImGui::BeginTabBar("##visTabs", ImGuiTabBarFlags_None)) {
        if (ImGui::BeginTabItem("Enemies")) {
            ImGui::BeginChild("ESP", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.65f, 253), true); {
                ImGui::Text("ESP");
                ImGui::Separator();
                if (CONFIGBOOL("Enemy:Box")) {
                    ImGui::ColorEdit4("Box Color", (float*)&CONFIGCOL("Enemy:BoxColor"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Box", &CONFIGBOOL("Enemy:Box"));
                ImGui::Checkbox("Name", &CONFIGBOOL("Enemy:Name"));
                ImGui::Checkbox("Health", &CONFIGBOOL("Enemy:Health"));
                ImGui::Checkbox("Health Bar", &CONFIGBOOL("Enemy:HealthBar"));
                ImGui::Checkbox("Money", &CONFIGBOOL("Enemy:Money"));
                ImGui::Checkbox("Only When Dead", &CONFIGBOOL("Enemy:DeadESP"));
                ImGui::EndChild();
            }
            ImGui::BeginChild("Chams", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.65f, 253), true); {
                ImGui::Text("Chams");
                ImGui::Separator();
                ImGui::Text("Visible");
                ImGui::PushItemWidth(ImGui::GetWindowContentRegionWidth() * 0.4f);
                ImGui::Combo("##VisMaterial", &CONFIGINT("Enemy:ChamsMaterial"), chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
                ImGui::SameLine();
                ImGui::ColorEdit4("##Chams Primary Color", (float*)&CONFIGCOL("Enemy:ChamsColor"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                ImGui::SameLine();
                ImGui::Combo("##VisOverlayMaterial", &CONFIGINT("Enemy:ChamsOverlayMaterial"), chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
                ImGui::SameLine();
                ImGui::ColorEdit4("##ChamsOverlayColor", (float*)&CONFIGCOL("Enemy:ChamsOverlayColor"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                
                ImGui::PushItemWidth(ImGui::GetWindowContentRegionWidth() * 0.9f);
                ImGui::Text("Occluded");
                ImGui::Combo("##IZMaterial", &CONFIGINT("Enemy:IgnoreZChamsMaterial"), chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
                ImGui::SameLine();
                ImGui::ColorEdit4("IgnoreZ Chams Primary Color", (float*)&CONFIGCOL("Enemy:IgnoreZChamsColor"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                ImGui::EndChild();
                ImGui::PushItemWidth(ImGui::GetWindowContentRegionWidth() * 0.65f);
            }
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Teammates")) {
            ImGui::BeginChild("ESP", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.65f, 253), true); {
                ImGui::Text("ESP");
                ImGui::Separator();
                if (CONFIGBOOL("Team:Box")) {
                    ImGui::ColorEdit4("Box Color", (float*)&CONFIGCOL("Team:BoxColor"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Box", &CONFIGBOOL("Team:Box"));

                ImGui::Checkbox("Name", &CONFIGBOOL("Team:Name"));
                ImGui::Checkbox("Health", &CONFIGBOOL("Team:Health"));
                ImGui::Checkbox("Health Bar", &CONFIGBOOL("Team:HealthBar"));
                ImGui::Checkbox("Money", &CONFIGBOOL("Team:Money"));
                ImGui::Checkbox("Only When Dead", &CONFIGBOOL("Team:DeadESP"));
                ImGui::EndChild();
            }
            ImGui::BeginChild("Chams", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.65f, 253), true); {
                ImGui::Text("Chams");
                ImGui::Separator();
                ImGui::Text("Visible");
                ImGui::PushItemWidth(ImGui::GetWindowContentRegionWidth() * 0.4f);
                ImGui::Combo("##VisMaterial", &CONFIGINT("Team:ChamsMaterial"), chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
                ImGui::SameLine();
                ImGui::ColorEdit4("##Chams Primary Color", (float*)&CONFIGCOL("Team:ChamsColor"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                ImGui::SameLine();
                ImGui::Combo("##VisOverlayMaterial", &CONFIGINT("Team:ChamsOverlayMaterial"), chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
                ImGui::SameLine();
                ImGui::ColorEdit4("##ChamsOverlayColor", (float*)&CONFIGCOL("Team:ChamsOverlayColor"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                
                ImGui::PushItemWidth(ImGui::GetWindowContentRegionWidth() * 0.9f);
                ImGui::Text("Occluded");
                ImGui::Combo("##IZMaterial", &CONFIGINT("Team:IgnoreZChamsMaterial"), chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
                ImGui::SameLine();
                ImGui::ColorEdit4("IgnoreZ Chams Primary Color", (float*)&CONFIGCOL("Team:IgnoreZChamsColor"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                ImGui::EndChild();
                ImGui::PushItemWidth(ImGui::GetWindowContentRegionWidth() * 0.65f);
            }
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("World")) {
            ImGui::BeginChild("Local Player", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.65f, 253), true); {
                ImGui::Text("Local Player");
                ImGui::Separator();
                ImGui::Text("Arm Chams");
                ImGui::PushItemWidth(ImGui::GetWindowContentRegionWidth() * 0.4f);
                ImGui::Combo("##ArmMaterial", &CONFIGINT("Arms:ChamsMaterial"), chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
                ImGui::SameLine();
                ImGui::ColorEdit4("##Arm Chams Primary Color", (float*)&CONFIGCOL("Arms:ChamsColor"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                ImGui::SameLine();
                ImGui::Combo("##ArmOverlayMaterial", &CONFIGINT("Arms:ChamsOverlayMaterial"), chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
                ImGui::SameLine();
                ImGui::ColorEdit4("##ArmOverlayColor", (float*)&CONFIGCOL("Arms:ChamsOverlayColor"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);

                ImGui::Text("Weapon Chams");
                ImGui::Combo("##WeaponMaterial", &CONFIGINT("Weapon:ChamsMaterial"), chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
                ImGui::SameLine();
                ImGui::ColorEdit4("##Weapon Chams Primary Color", (float*)&CONFIGCOL("Weapon:ChamsColor"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                ImGui::SameLine();
                ImGui::Combo("##WeaponOverlayMaterial", &CONFIGINT("Weapon:ChamsOverlayMaterial"), chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
                ImGui::SameLine();
                ImGui::ColorEdit4("##WeaponOverlayColor", (float*)&CONFIGCOL("Weapon:ChamsOverlayColor"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                ImGui::PushItemWidth(ImGui::GetWindowContentRegionWidth() * 0.65f);

                ImGui::Checkbox("Spread Crosshair", &CONFIGBOOL("World:SpreadCrosshair"));
                ImGui::SameLine();
                ImGui::Checkbox("Recoil Crosshair", &CONFIGBOOL("World:RecoilCrosshair"));
                if (CONFIGBOOL("World:SpreadCrosshair") || CONFIGBOOL("World:RecoilCrosshair")) {
                    ImGui::SameLine();
                    ImGui::ColorEdit4("##CrosshairColour", (float*)&CONFIGCOL("World:SpreadCrosshairColor"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                    ImGui::SameLine();
                    ImGui::ColorEdit4("##CrosshairBorderColour", (float*)&CONFIGCOL("World:SpreadCrosshairBorderColor"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                }
                ImGui::EndChild();
            }
            ImGui::SameLine();
            ImGui::BeginChild("Items", ImVec2(0, 253), true); {
                ImGui::Text("Items");
                ImGui::Separator();
                if (CONFIGBOOL("Weapon:Box")) {
                    ImGui::ColorEdit4("Weapon Box Color", (float*)&CONFIGCOL("Weapon:BoxColor"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Weapon Box", &CONFIGBOOL("Weapon:Box"));
                ImGui::Checkbox("Weapon Label", &CONFIGBOOL("Weapon:Name"));
                ImGui::Separator();
                if (CONFIGBOOL("PlantedC4:Box")) {
                    ImGui::ColorEdit4("Planted C4 Box Color", (float*)&CONFIGCOL("PlantedC4:BoxColor"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Planted C4 Box", &CONFIGBOOL("PlantedC4:Box"));
                ImGui::Checkbox("Planted C4 Label", &CONFIGBOOL("PlantedC4:Name"));
                ImGui::Separator();
                if (CONFIGBOOL("Chicken:Box")) {
                    ImGui::ColorEdit4("Chicken Box Color", (float*)&CONFIGCOL("Chicken:BoxColor"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Chicken Box", &CONFIGBOOL("Chicken:Box"));
                ImGui::Checkbox("Chicken Label", &CONFIGBOOL("Chicken:Name"));
                ImGui::Separator();
                if (CONFIGBOOL("Fish:Box")) {
                    ImGui::ColorEdit4("Fish Box Color", (float*)&CONFIGCOL("Fish:BoxColor"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Fish Box", &CONFIGBOOL("Fish:Box"));
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