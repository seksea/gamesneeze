#include "../menu.hpp"

const char* chamsMaterials[] = {"None", "Shaded", "Flat", "Screen Pulse", "Energy Ball", "Glow", "Plastic", "Darude"};

void Menu::drawVisualsTab() {
    ImGui::Text("Visuals");
    if (ImGui::BeginTabBar("##visTabs", ImGuiTabBarFlags_None)) {
        if (ImGui::BeginTabItem("Enemies")) {
            ImGui::BeginChild("ESP", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.65f, 253), true); {
                ImGui::Text("ESP");
                ImGui::Separator();
                if (CONFIGBOOL("Visuals>Enemies>ESP>Box")) {
                    ImGui::ColorEdit4("Box Color", (float*)&CONFIGCOL("Visuals>Enemies>ESP>Box Color"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Box", &CONFIGBOOL("Visuals>Enemies>ESP>Box"));
                ImGui::Checkbox("Name", &CONFIGBOOL("Visuals>Enemies>ESP>Name"));
                ImGui::Checkbox("Health", &CONFIGBOOL("Visuals>Enemies>ESP>Health"));
                ImGui::Checkbox("Health Bar", &CONFIGBOOL("Visuals>Enemies>ESP>Health Bar"));
                ImGui::Checkbox("Health Bar Color", &CONFIGBOOL("Visuals>ESP>Health Bar>Color"));
                ImGui::Checkbox("Money", &CONFIGBOOL("Visuals>Enemies>ESP>Money"));
                ImGui::Checkbox("Only When Dead", &CONFIGBOOL("Visuals>Enemies>ESP>Only When Dead"));
                ImGui::EndChild();
            }
            ImGui::BeginChild("Chams", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.65f, 253), true); {
                ImGui::Text("Chams");
                ImGui::Separator();
                ImGui::Text("Visible");
                ImGui::PushItemWidth(ImGui::GetWindowContentRegionWidth() * 0.4f);
                ImGui::Combo("##Visible Material", &CONFIGINT("Visuals>Enemies>Chams>Visible Material"), chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
                ImGui::SameLine();
                ImGui::ColorEdit4("Visible Color", (float*)&CONFIGCOL("Visuals>Enemies>Chams>Visible Color"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                ImGui::SameLine();
                ImGui::Combo("##Visible Overlay Material", &CONFIGINT("Visuals>Enemies>Chams>Visible Overlay Material"), chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
                ImGui::SameLine();
                ImGui::ColorEdit4("Visible Overlay Color", (float*)&CONFIGCOL("Visuals>Enemies>Chams>Visible Overlay Color"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                
                ImGui::PushItemWidth(ImGui::GetWindowContentRegionWidth() * 0.9f);
                ImGui::Text("Occluded");
                ImGui::Combo("##Occluded Material", &CONFIGINT("Visuals>Enemies>Chams>Occluded Material"), chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
                ImGui::SameLine();
                ImGui::ColorEdit4("Occluded Color", (float*)&CONFIGCOL("Visuals>Enemies>Chams>Occluded Color"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                ImGui::EndChild();
                ImGui::PushItemWidth(ImGui::GetWindowContentRegionWidth() * 0.65f);
            }
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Teammates")) {
            ImGui::BeginChild("ESP", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.65f, 253), true); {
                ImGui::Text("ESP");
                ImGui::Separator();
                if (CONFIGBOOL("Visuals>Teammates>ESP>Box")) {
                    ImGui::ColorEdit4("Box Color", (float*)&CONFIGCOL("Visuals>Teammates>ESP>Box Color"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Box", &CONFIGBOOL("Visuals>Teammates>ESP>Box"));

                ImGui::Checkbox("Name", &CONFIGBOOL("Visuals>Teammates>ESP>Name"));
                ImGui::Checkbox("Health", &CONFIGBOOL("Visuals>Teammates>ESP>Health"));
                ImGui::Checkbox("Health Bar", &CONFIGBOOL("Visuals>Teammates>ESP>Health Bar"));
                ImGui::Checkbox("Health Bar Color", &CONFIGBOOL("Visuals>ESP>Health Bar>Color"));
                ImGui::Checkbox("Money", &CONFIGBOOL("Visuals>Teammates>ESP>Money"));
                ImGui::Checkbox("Only When Dead", &CONFIGBOOL("Visuals>Teammates>ESP>Only When Dead"));
                ImGui::EndChild();
            }
            ImGui::BeginChild("Chams", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.65f, 253), true); {
                ImGui::Text("Chams");
                ImGui::Separator();
                ImGui::Text("Visible");
                ImGui::PushItemWidth(ImGui::GetWindowContentRegionWidth() * 0.4f);
                ImGui::Combo("##Visible Material", &CONFIGINT("Visuals>Teammates>Chams>Visible Material"), chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
                ImGui::SameLine();
                ImGui::ColorEdit4("Visible Color", (float*)&CONFIGCOL("Visuals>Teammates>Chams>Visible Color"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                ImGui::SameLine();
                ImGui::Combo("##Visible Overlay Material", &CONFIGINT("Visuals>Teammates>Chams>Visible Overlay Material"), chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
                ImGui::SameLine();
                ImGui::ColorEdit4("Visible Overlay Color", (float*)&CONFIGCOL("Visuals>Teammates>Chams>Visible Overlay Color"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                
                ImGui::PushItemWidth(ImGui::GetWindowContentRegionWidth() * 0.9f);
                ImGui::Text("Occluded");
                ImGui::Combo("##Occluded Material", &CONFIGINT("Visuals>Teammates>Chams>Occluded Material"), chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
                ImGui::SameLine();
                ImGui::ColorEdit4("Occluded Color", (float*)&CONFIGCOL("Visuals>Teammates>Chams>Occluded Color"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
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
                ImGui::Combo("##Arms Material", &CONFIGINT("Visuals>World>Local Player>Arms Material"), chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
                ImGui::SameLine();
                ImGui::ColorEdit4("Arms Color", (float*)&CONFIGCOL("Visuals>World>Local Player>Arms Color"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                ImGui::SameLine();
                ImGui::Combo("##Arms Overlay Material", &CONFIGINT("Visuals>World>Local Player>Arms Overlay Material"), chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
                ImGui::SameLine();
                ImGui::ColorEdit4("Arms Overlay Color", (float*)&CONFIGCOL("Visuals>World>Local Player>Arms Overlay Color"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);

                ImGui::Text("Weapon Chams");
                ImGui::Combo("##Weapon Material", &CONFIGINT("Visuals>World>Local Player>Weapon Material"), chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
                ImGui::SameLine();
                ImGui::ColorEdit4("Weapon Color", (float*)&CONFIGCOL("Visuals>World>Local Player>Weapon Color"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                ImGui::SameLine();
                ImGui::Combo("##Weapon Overlay Material", &CONFIGINT("Visuals>World>Local Player>Weapon Overlay Material"), chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
                ImGui::SameLine();
                ImGui::ColorEdit4("Weapon Overlay Color", (float*)&CONFIGCOL("Visuals>World>Local Player>Weapon Overlay Color"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                ImGui::PushItemWidth(ImGui::GetWindowContentRegionWidth() * 0.65f);

                ImGui::ColorEdit4("Crosshair Color", (float*)&CONFIGCOL("Visuals>World>Local Player>Crosshair Color"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                ImGui::SameLine();
                ImGui::ColorEdit4("Crosshair Border Color", (float*)&CONFIGCOL("Visuals>World>Local Player>Crosshair Border Color"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                ImGui::SameLine();
                ImGui::Checkbox("Spread Crosshair", &CONFIGBOOL("Visuals>World>Local Player>Spread Crosshair"));
                ImGui::SameLine();
                ImGui::Checkbox("Recoil Crosshair", &CONFIGBOOL("Visuals>World>Local Player>Recoil Crosshair"));
                //make sure they can't both be on at the same time
                if (CONFIGBOOL("Visuals>World>Local Player>Recoil Crosshair") && !CONFIGBOOL("Visuals>World>Local Player>Spread Crosshair")) {
                    ImGui::SameLine();
                    ImGui::Checkbox("Only When Shooting", &CONFIGBOOL("Visuals>World>Local Player>Recoil Crosshair>Only When Shooting"));
                }
                if (CONFIGBOOL("Visuals>World>Local Player>Spread Crosshair") || CONFIGBOOL("Visuals>World>Local Player>Recoil Crosshair")) {
                    ImGui::SameLine();
                }
                ImGui::EndChild();
            }
            ImGui::SameLine();
            ImGui::BeginChild("Items", ImVec2(0, 253), true); {
                ImGui::Text("Items");
                ImGui::Separator();
                if (CONFIGBOOL("Visuals>World>Items>Weapon Box")) {
                    ImGui::ColorEdit4("Weapon Box Color", (float*)&CONFIGCOL("Visuals>World>Items>Weapon Box Color"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Weapon Box", &CONFIGBOOL("Visuals>World>Items>Weapon Box"));
                ImGui::Checkbox("Weapon Label", &CONFIGBOOL("Visuals>World>Items>Weapon Label"));
                ImGui::Separator();
                if (CONFIGBOOL("Visuals>World>Items>Planted C4 Box")) {
                    ImGui::ColorEdit4("Planted C4 Box Color", (float*)&CONFIGCOL("Visuals>World>Items>Planted C4 Box Color"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Planted C4 Box", &CONFIGBOOL("Visuals>World>Items>Planted C4 Box"));
                ImGui::Checkbox("Planted C4 Label", &CONFIGBOOL("Visuals>World>Items>Planted C4 Label"));
                ImGui::Separator();
                if (CONFIGBOOL("Visuals>World>Items>Chicken Box")) {
                    ImGui::ColorEdit4("Chicken Box Color", (float*)&CONFIGCOL("Visuals>World>Items>Chicken Box Color"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Chicken Box", &CONFIGBOOL("Visuals>World>Items>Chicken Box"));
                ImGui::Checkbox("Chicken Label", &CONFIGBOOL("Visuals>World>Items>Chicken Label"));
                ImGui::Separator();
                if (CONFIGBOOL("Visuals>World>Items>Fish Box")) {
                    ImGui::ColorEdit4("Fish Box Color", (float*)&CONFIGCOL("Visuals>World>Items>Fish Box Color"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Fish Box", &CONFIGBOOL("Visuals>World>Items>Fish Box"));
                ImGui::Checkbox("Fish Label", &CONFIGBOOL("Visuals>World>Items>Fish Label"));
                ImGui::Separator();

                ImGui::Checkbox("ESP Quite literally everything", &CONFIGBOOL("Visuals>World>Items>ESP Quite literally everything"));
                ImGui::EndChild();
            }
            ImGui::BeginChild("World", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.65f, 253), true); {
                ImGui::Text("World");
                ImGui::Separator();
                if (
                  ImGui::ColorEdit4("World Color Modulation", (float*)&CONFIGCOL("Visuals>World>World>World Color Modulation"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel) || 
                  ImGui::Button("Update Color Modulation")) {
                    Features::WorldColorModulate::updateColorModulation();
                }

                ImGui::EndChild();
            }
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }
}