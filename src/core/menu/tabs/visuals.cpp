#include "../menu.hpp"

const char* chamsMaterials[] = {"None", "Shaded", "Flat", "Screen Pulse", "Energy Ball", "Glow", "Plastic", "Darude", "Oil"};

void drawChamsWidget(const char* label, 
                    int* material, ImColor* color, 
                    int* overlayMaterial, ImColor* overlayColor,
                    bool occluded = false, int* occludedMaterial = nullptr, ImColor* occludedColor = nullptr,
                    bool backtrack = false, int* backtrackMaterial = nullptr, ImColor* backtrackColor = nullptr, bool* backtrackTrail = nullptr) {
    char btnLabel[64];
    snprintf(btnLabel, sizeof(btnLabel), "Chams##%s", label);
    if (ImGui::Button(btnLabel)) {
        ImGui::OpenPopup(btnLabel);
    }
    if (ImGui::BeginPopup(btnLabel)) {
        ImGui::Text("%s Chams", label);
        ImGui::Separator();
        ImGui::Text("%s Chams", label);
        ImGui::Combo("##Chams Material", material, chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
        ImGui::SameLine();
        ImGui::ColorEdit4("##Chams Color", (float*)color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);

        ImGui::Text("%s Chams Overlay", label);
        ImGui::Combo("##Chams Overlay Material", overlayMaterial, chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
        ImGui::SameLine();
        ImGui::ColorEdit4("Chams Overlay Color", (float*)overlayColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);

        if (occluded) {
            ImGui::Separator();

            ImGui::Text("%s Occluded Chams", label);
            ImGui::Combo("##Occluded Chams Material", occludedMaterial, chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
            ImGui::SameLine();
            ImGui::ColorEdit4("Occluded Chams Color", (float*)occludedColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
        }
        if (backtrack) {
            ImGui::Separator();

            ImGui::Text("%s Backtrack Chams", label);
            ImGui::Combo("##Backtrack Chams Material", backtrackMaterial, chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
            ImGui::SameLine();
            ImGui::ColorEdit4("Backtrack Chams Color", (float*)backtrackColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
            ImGui::Checkbox("Trail", backtrackTrail);
        }
        ImGui::EndPopup();
    }
}

void Menu::drawVisualsTab() {
    if (ImGui::BeginTabBar("##visTabs")) {
        if (ImGui::BeginTabItem("Players")) {
            ImGui::BeginChild("Teammates", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.325f, ImGui::GetWindowHeight() * 0.875f), true); {
                ImGui::Text("Teammates");
                ImGui::Separator();

                if (CONFIGBOOL("Visuals>Players>Teammates>Box")) {
                    ImGui::ColorEdit4("Box Color", (float*)&CONFIGCOL("Visuals>Players>Teammates>Box Color"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Box", &CONFIGBOOL("Visuals>Players>Teammates>Box"));

                if (CONFIGBOOL("Visuals>Players>Teammates>Skeleton")) {
                    ImGui::ColorEdit4("Skeleton Color", (float*)&CONFIGCOL("Visuals>Players>Teammates>Skeleton Color"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Skeleton", &CONFIGBOOL("Visuals>Players>Teammates>Skeleton"));

                ImGui::Checkbox("Name", &CONFIGBOOL("Visuals>Players>Teammates>Name"));
                ImGui::Checkbox("Health", &CONFIGBOOL("Visuals>Players>Teammates>Health"));
                if(CONFIGBOOL("Visuals>Players>Teammates>Health Bar")) {
                    ImGui::ColorEdit4("Health Bar Color", (float*)&CONFIGCOL("Visuals>Players>Teammates>Health Bar Color"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Health Bar", &CONFIGBOOL("Visuals>Players>Teammates>Health Bar"));
                if(CONFIGBOOL("Visuals>Players>Teammates>Health Bar")) {
                    ImGui::SameLine();
                    ImGui::Checkbox("Dynamic Color", &CONFIGBOOL("Visuals>Players>Teammates>Dynamic Color"));
                }
                ImGui::Checkbox("Money", &CONFIGBOOL("Visuals>Players>Teammates>Money"));
                ImGui::Checkbox("Only When Dead", &CONFIGBOOL("Visuals>Players>Teammates>Only When Dead"));

                drawChamsWidget("Teammates", 
                    &CONFIGINT("Visuals>Players>Teammates>Chams>Visible Material"), &CONFIGCOL("Visuals>Players>Teammates>Chams>Visible Color"), 
                    &CONFIGINT("Visuals>Players>Teammates>Chams>Visible Overlay Material"), &CONFIGCOL("Visuals>Players>Teammates>Chams>Visible Overlay Color"), 
                    true, &CONFIGINT("Visuals>Players>Teammates>Chams>Occluded Material"), &CONFIGCOL("Visuals>Players>Teammates>Chams>Occluded Color"));

                ImGui::EndChild();
            }
            ImGui::SameLine();
            ImGui::BeginChild("Enemies", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.325f, ImGui::GetWindowHeight() * 0.875f), true); {
                ImGui::Text("Enemies");
                ImGui::Separator();

                if (CONFIGBOOL("Visuals>Players>Enemies>Box")) {
                    ImGui::ColorEdit4("Box Color", (float*)&CONFIGCOL("Visuals>Players>Enemies>Box Color"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Box", &CONFIGBOOL("Visuals>Players>Enemies>Box"));

                if (CONFIGBOOL("Visuals>Players>Enemies>Skeleton")) {
                    ImGui::ColorEdit4("Skeleton Color", (float*)&CONFIGCOL("Visuals>Players>Enemies>Skeleton Color"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Skeleton", &CONFIGBOOL("Visuals>Players>Enemies>Skeleton"));

                ImGui::Checkbox("Name", &CONFIGBOOL("Visuals>Players>Enemies>Name"));
                ImGui::Checkbox("Health", &CONFIGBOOL("Visuals>Players>Enemies>Health"));
                if(CONFIGBOOL("Visuals>Players>Enemies>Health Bar")) {
                    ImGui::ColorEdit4("Health Bar Color", (float*)&CONFIGCOL("Visuals>Players>Enemies>Health Bar Color"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Health Bar", &CONFIGBOOL("Visuals>Players>Enemies>Health Bar"));
                if(CONFIGBOOL("Visuals>Players>Enemies>Health Bar")) {
                    ImGui::SameLine();
                    ImGui::Checkbox("Dynamic Color", &CONFIGBOOL("Visuals>Players>Enemies>Dynamic Color"));
                }
                ImGui::Checkbox("Money", &CONFIGBOOL("Visuals>Players>Enemies>Money"));
                ImGui::Checkbox("Radar", &CONFIGBOOL("Visuals>Players>Enemies>Radar"));
                ImGui::Checkbox("Forwardtrack Dots", &CONFIGBOOL("Visuals>Players>Enemies>Forwardtrack Dots"));
                ImGui::Checkbox("Vis Check", &CONFIGBOOL("Visuals>Players>Enemies>Vis Check"));
                ImGui::Checkbox("Only When Dead", &CONFIGBOOL("Visuals>Players>Enemies>Only When Dead"));

                drawChamsWidget("Enemies", 
                    &CONFIGINT("Visuals>Players>Enemies>Chams>Visible Material"), &CONFIGCOL("Visuals>Players>Enemies>Chams>Visible Color"), 
                    &CONFIGINT("Visuals>Players>Enemies>Chams>Visible Overlay Material"), &CONFIGCOL("Visuals>Players>Enemies>Chams>Visible Overlay Color"), 
                    true, &CONFIGINT("Visuals>Players>Enemies>Chams>Occluded Material"), &CONFIGCOL("Visuals>Players>Enemies>Chams>Occluded Color"), 
                    true, &CONFIGINT("Visuals>Players>Enemies>Chams>Backtrack Material"), &CONFIGCOL("Visuals>Players>Enemies>Chams>Backtrack Color"), &CONFIGBOOL("Visuals>Players>Enemies>Chams>Trail"));

                ImGui::EndChild();
            }
            ImGui::SameLine();
            ImGui::BeginChild("LocalPlayer", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.325f, ImGui::GetWindowHeight() * 0.875f), true); {
                ImGui::Text("LocalPlayer");
                ImGui::Separator();

                ImGui::Text("Arms");
                drawChamsWidget("Arm",
                    &CONFIGINT("Visuals>Players>LocalPlayer>Arms Material"), &CONFIGCOL("Visuals>Players>LocalPlayer>Arms Color"), 
                    &CONFIGINT("Visuals>Players>LocalPlayer>Arms Overlay Material"), &CONFIGCOL("Visuals>Players>LocalPlayer>Arms Overlay Color"));
                ImGui::Separator();
                ImGui::Text("Weapons");
                drawChamsWidget("Weapon",
                    &CONFIGINT("Visuals>Players>LocalPlayer>Weapon Material"), &CONFIGCOL("Visuals>Players>LocalPlayer>Weapon Color"), 
                    &CONFIGINT("Visuals>Players>LocalPlayer>Weapon Overlay Material"), &CONFIGCOL("Visuals>Players>LocalPlayer>Weapon Overlay Color"));

                ImGui::Separator();
                ImGui::ColorEdit4("Crosshair Color", (float*)&CONFIGCOL("Visuals>Players>LocalPlayer>Crosshair Color"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                ImGui::SameLine();
                ImGui::ColorEdit4("Crosshair Border Color", (float*)&CONFIGCOL("Visuals>Players>LocalPlayer>Crosshair Border Color"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                ImGui::SameLine();
                ImGui::Checkbox("Spread Crosshair", &CONFIGBOOL("Visuals>Players>LocalPlayer>Spread Crosshair"));
                ImGui::Checkbox("Recoil Crosshair", &CONFIGBOOL("Visuals>Players>LocalPlayer>Recoil Crosshair"));
                // Make sure they can't both be on at the same time
                if (CONFIGBOOL("Visuals>Players>LocalPlayer>Recoil Crosshair") && !CONFIGBOOL("Visuals>Players>LocalPlayer>Spread Crosshair")) {
                    ImGui::Checkbox("Only When Shooting", &CONFIGBOOL("Visuals>Players>LocalPlayer>Recoil Crosshair>Only When Shooting"));
                }
                ImGui::EndChild();
            }
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("World")) {
            ImGui::BeginChild("World", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.65f, ImGui::GetWindowHeight() * 0.875f), true); {
                ImGui::Text("World");
                ImGui::Separator();
                if (
                  ImGui::ColorEdit4("World Color Modulation", (float*)&CONFIGCOL("Visuals>World>World>World Color Modulation"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel) || 
                  ImGui::Button("Update Color Modulation")) {
                    Features::WorldColorModulate::updateColorModulation();
                }

                ImGui::Text("NightMode");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##NightMode", &CONFIGINT("Visuals>World>World>Nightmode"), 0, 100);
                ImGui::Text("Skybox");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::Combo("##Skybox", &CONFIGINT("Visuals>World>World>Skybox"), skyboxes, IM_ARRAYSIZE(skyboxes));
                ImGui::Text("FOV");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##FOV", &CONFIGINT("Visuals>World>World>FOV"), 70, 120);
                ImGui::Checkbox("Third Person", &CONFIGBOOL("Visuals>World>World>Third Person"));
                ImGui::Checkbox("Third Person Shows Fake", &CONFIGBOOL("Visuals>World>World>Third Person Shows Fake"));
                ImGui::Checkbox("No Flash", &CONFIGBOOL("Visuals>World>World>No Flash"));
                ImGui::EndChild();
            }
            ImGui::SameLine();
            ImGui::BeginChild("Items", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.34f, ImGui::GetWindowHeight() * 0.875f), true); {
                ImGui::Text("Items");
                ImGui::Separator();
                if (CONFIGBOOL("Visuals>World>Items>Weapon Box")) {
                    ImGui::ColorEdit4("Weapon Box Color", (float*)&CONFIGCOL("Visuals>World>Items>Weapon Box Color"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Weapon Box", &CONFIGBOOL("Visuals>World>Items>Weapon Box"));
                ImGui::Checkbox("Weapon Label", &CONFIGBOOL("Visuals>World>Items>Weapon Label"));
                ImGui::Separator();
                if (CONFIGBOOL("Visuals>World>Items>Grenade Box")) {
                    ImGui::ColorEdit4("Weapon Box Color", (float*)&CONFIGCOL("Visuals>World>Items>Grenade Box Color"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Grenade Box", &CONFIGBOOL("Visuals>World>Items>Grenade Box"));
                if (CONFIGBOOL("Visuals>World>Items>Grenade Box")) {
                    ImGui::SameLine();
                    ImGui::Checkbox("Dynamic Color", &CONFIGBOOL("Visuals>World>Items>Grenade Box Dynamic Color"));
                }
                ImGui::Checkbox("Grenade Label", &CONFIGBOOL("Visuals>World>Items>Grenade Label"));
                ImGui::Checkbox("Grenade Owners", &CONFIGBOOL("Visuals>World>Items>Grenade Owners"));
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
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
}