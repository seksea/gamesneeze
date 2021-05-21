#include "../menu.hpp"

void Menu::drawLegitTab() {
    ImGui::BeginChild("LegitBot", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.65f, 260), true); {
        ImGui::Text("LegitBot");
        ImGui::Separator();
        if (ImGui::BeginTabBar("Aim Weapons Tabbar")) {
            if (ImGui::BeginTabItem("Default")) {
                static bool keybindToggled;
                Menu::CustomWidgets::drawKeyBinder("Key", &CONFIGINT("Legit>LegitBot>Default>Key"), &keybindToggled);
                ImGui::SameLine();
                ImGui::Checkbox("Always On", &CONFIGBOOL("Legit>LegitBot>Default>Always on"));
                ImGui::Text("FOV (x10)");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##FOV", &CONFIGINT("Legit>LegitBot>Default>FOV"), 0, 1800);
                ImGui::Text("Smoothing");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Smoothing", &CONFIGINT("Legit>LegitBot>Default>Smoothing"), 0, 100);
                ImGui::Checkbox("Recoil Compensation", &CONFIGBOOL("Legit>LegitBot>Default>Recoil Compensation"));
                if (CONFIGBOOL("Legit>LegitBot>Default>Recoil Compensation")) {
                    ImGui::Text("RCS Amount X");
                    ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                    ImGui::SliderInt("##RCS Amount X", &CONFIGINT("Legit>LegitBot>Default>RCS Amount X"), 0, 100);
                    ImGui::Text("RCS Amount Y");
                    ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                    ImGui::SliderInt("##RCS Amount Y", &CONFIGINT("Legit>LegitBot>Default>RCS Amount Y"), 0, 100);
                }

                ImGui::Checkbox("Flash Check", &CONFIGBOOL("Legit>LegitBot>Default>Flash Check"));
                ImGui::Checkbox("Jump Check", &CONFIGBOOL("Legit>LegitBot>Default>Jump Check"));
                ImGui::Checkbox("Enemy Jump Check", &CONFIGBOOL("Legit>LegitBot>Default>Enemy Jump Check"));

                ImGui::Text("Hitboxes");
                ImGui::Checkbox("Head", &CONFIGBOOL("Legit>LegitBot>Default>Head"));
                ImGui::Checkbox("Chest", &CONFIGBOOL("Legit>LegitBot>Default>Chest"));
                ImGui::Checkbox("Stomach", &CONFIGBOOL("Legit>LegitBot>Default>Stomach"));
                ImGui::Checkbox("Pelvis", &CONFIGBOOL("Legit>LegitBot>Default>Pelvis"));

                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Pistol")) {
                ImGui::Checkbox("Override", &CONFIGBOOL("Legit>LegitBot>Pistol>Override"));
                ImGui::Text("FOV (x10)");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##FOV", &CONFIGINT("Legit>LegitBot>Pistol>FOV"), 0, 1800);
                ImGui::Text("Smoothing");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Smoothing", &CONFIGINT("Legit>LegitBot>Pistol>Smoothing"), 0, 100);

                ImGui::Checkbox("Flash Check", &CONFIGBOOL("Legit>LegitBot>Pistol>Flash Check"));
                ImGui::Checkbox("Jump Check", &CONFIGBOOL("Legit>LegitBot>Pistol>Jump Check"));
                ImGui::Checkbox("Enemy Jump Check", &CONFIGBOOL("Legit>LegitBot>Pistol>Enemy Jump Check"));

                ImGui::Text("Hitboxes");
                ImGui::Checkbox("Head", &CONFIGBOOL("Legit>LegitBot>Pistol>Head"));
                ImGui::Checkbox("Chest", &CONFIGBOOL("Legit>LegitBot>Pistol>Chest"));
                ImGui::Checkbox("Stomach", &CONFIGBOOL("Legit>LegitBot>Pistol>Stomach"));
                ImGui::Checkbox("Pelvis", &CONFIGBOOL("Legit>LegitBot>Pistol>Pelvis"));

                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Heavy Pistol")) {
                ImGui::Checkbox("Override", &CONFIGBOOL("Legit>LegitBot>Heavy Pistol>Override"));
                ImGui::Text("FOV (x10)");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##FOV", &CONFIGINT("Legit>LegitBot>Heavy Pistol>FOV"), 0, 1800);
                ImGui::Text("Smoothing");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Smoothing", &CONFIGINT("Legit>LegitBot>Heavy Pistol>Smoothing"), 0, 100);

                ImGui::Checkbox("Flash Check", &CONFIGBOOL("Legit>LegitBot>Heavy Pistol>Flash Check"));
                ImGui::Checkbox("Jump Check", &CONFIGBOOL("Legit>LegitBot>Heavy Pistol>Jump Check"));
                ImGui::Checkbox("Enemy Jump Check", &CONFIGBOOL("Legit>LegitBot>Heavy Pistol>Enemy Jump Check"));

                ImGui::Text("Hitboxes");
                ImGui::Checkbox("Head", &CONFIGBOOL("Legit>LegitBot>Heavy Pistol>Head"));
                ImGui::Checkbox("Chest", &CONFIGBOOL("Legit>LegitBot>Heavy Pistol>Chest"));
                ImGui::Checkbox("Stomach", &CONFIGBOOL("Legit>LegitBot>Heavy Pistol>Stomach"));
                ImGui::Checkbox("Pelvis", &CONFIGBOOL("Legit>LegitBot>Heavy Pistol>Pelvis"));

                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Rifle")) {
                ImGui::Checkbox("Override", &CONFIGBOOL("Legit>LegitBot>Rifle>Override"));
                ImGui::Text("FOV (x10)");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##FOV", &CONFIGINT("Legit>LegitBot>Rifle>FOV"), 0, 1800);
                ImGui::Text("Smoothing");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Smoothing", &CONFIGINT("Legit>LegitBot>Rifle>Smoothing"), 0, 100);
                ImGui::Checkbox("Recoil Compensation", &CONFIGBOOL("Legit>LegitBot>Rifle>Recoil Compensation"));
                if (CONFIGBOOL("Legit>LegitBot>Rifle>Recoil Compensation")) {
                    ImGui::Text("RCS Amount X");
                    ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                    ImGui::SliderInt("##RCS Amount X", &CONFIGINT("Legit>LegitBot>Rifle>RCS Amount X"), 0, 100);
                    ImGui::Text("RCS Amount Y");
                    ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                    ImGui::SliderInt("##RCS Amount Y", &CONFIGINT("Legit>LegitBot>Rifle>RCS Amount Y"), 0, 100);
                }

                ImGui::Checkbox("Flash Check", &CONFIGBOOL("Legit>LegitBot>Rifle>Flash Check"));
                ImGui::Checkbox("Jump Check", &CONFIGBOOL("Legit>LegitBot>Rifle>Jump Check"));
                ImGui::Checkbox("Enemy Jump Check", &CONFIGBOOL("Legit>LegitBot>Rifle>Enemy Jump Check"));

                ImGui::Text("Hitboxes");
                ImGui::Checkbox("Head", &CONFIGBOOL("Legit>LegitBot>Rifle>Head"));
                ImGui::Checkbox("Chest", &CONFIGBOOL("Legit>LegitBot>Rifle>Chest"));
                ImGui::Checkbox("Stomach", &CONFIGBOOL("Legit>LegitBot>Rifle>Stomach"));
                ImGui::Checkbox("Pelvis", &CONFIGBOOL("Legit>LegitBot>Rifle>Pelvis"));

                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("SMG")) {
                ImGui::Checkbox("Override", &CONFIGBOOL("Legit>LegitBot>SMG>Override"));
                ImGui::Text("FOV (x10)");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##FOV", &CONFIGINT("Legit>LegitBot>SMG>FOV"), 0, 1800);
                ImGui::Text("Smoothing");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Smoothing", &CONFIGINT("Legit>LegitBot>SMG>Smoothing"), 0, 100);
                ImGui::Checkbox("Recoil Compensation", &CONFIGBOOL("Legit>LegitBot>SMG>Recoil Compensation"));
                if (CONFIGBOOL("Legit>LegitBot>SMG>Recoil Compensation")) {
                    ImGui::Text("RCS Amount X");
                    ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                    ImGui::SliderInt("##RCS Amount X", &CONFIGINT("Legit>LegitBot>SMG>RCS Amount X"), 0, 100);
                    ImGui::Text("RCS Amount Y");
                    ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                    ImGui::SliderInt("##RCS Amount Y", &CONFIGINT("Legit>LegitBot>SMG>RCS Amount Y"), 0, 100);
                }

                ImGui::Checkbox("Flash Check", &CONFIGBOOL("Legit>LegitBot>SMG>Flash Check"));
                ImGui::Checkbox("Jump Check", &CONFIGBOOL("Legit>LegitBot>SMG>Jump Check"));
                ImGui::Checkbox("Enemy Jump Check", &CONFIGBOOL("Legit>LegitBot>SMG>Enemy Jump Check"));

                ImGui::Text("Hitboxes");
                ImGui::Checkbox("Head", &CONFIGBOOL("Legit>LegitBot>SMG>Head"));
                ImGui::Checkbox("Chest", &CONFIGBOOL("Legit>LegitBot>SMG>Chest"));
                ImGui::Checkbox("Stomach", &CONFIGBOOL("Legit>LegitBot>SMG>Stomach"));
                ImGui::Checkbox("Pelvis", &CONFIGBOOL("Legit>LegitBot>SMG>Pelvis"));

                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Scout")) {
                ImGui::Checkbox("Override", &CONFIGBOOL("Legit>LegitBot>Scout>Override"));
                ImGui::Text("FOV (x10)");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##FOV", &CONFIGINT("Legit>LegitBot>Scout>FOV"), 0, 1800);
                ImGui::Text("Smoothing");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Smoothing", &CONFIGINT("Legit>LegitBot>Scout>Smoothing"), 0, 100);

                ImGui::Checkbox("Flash Check", &CONFIGBOOL("Legit>LegitBot>Scout>Flash Check"));
                ImGui::Checkbox("Jump Check", &CONFIGBOOL("Legit>LegitBot>Scout>Jump Check"));
                ImGui::Checkbox("Enemy Jump Check", &CONFIGBOOL("Legit>LegitBot>Scout>Enemy Jump Check"));

                ImGui::Text("Hitboxes");
                ImGui::Checkbox("Head", &CONFIGBOOL("Legit>LegitBot>Scout>Head"));
                ImGui::Checkbox("Chest", &CONFIGBOOL("Legit>LegitBot>Scout>Chest"));
                ImGui::Checkbox("Stomach", &CONFIGBOOL("Legit>LegitBot>Scout>Stomach"));
                ImGui::Checkbox("Pelvis", &CONFIGBOOL("Legit>LegitBot>Scout>Pelvis"));

                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("AWP")) {
                ImGui::Checkbox("Override", &CONFIGBOOL("Legit>LegitBot>AWP>Override"));
                ImGui::Text("FOV (x10)");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##FOV", &CONFIGINT("Legit>LegitBot>AWP>FOV"), 0, 1800);
                ImGui::Text("Smoothing");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Smoothing", &CONFIGINT("Legit>LegitBot>AWP>Smoothing"), 0, 100);

                ImGui::Checkbox("Flash Check", &CONFIGBOOL("Legit>LegitBot>AWP>Flash Check"));
                ImGui::Checkbox("Jump Check", &CONFIGBOOL("Legit>LegitBot>AWP>Jump Check"));
                ImGui::Checkbox("Enemy Jump Check", &CONFIGBOOL("Legit>LegitBot>AWP>Enemy Jump Check"));

                ImGui::Text("Hitboxes");
                ImGui::Checkbox("Head", &CONFIGBOOL("Legit>LegitBot>AWP>Head"));
                ImGui::Checkbox("Chest", &CONFIGBOOL("Legit>LegitBot>AWP>Chest"));
                ImGui::Checkbox("Stomach", &CONFIGBOOL("Legit>LegitBot>AWP>Stomach"));
                ImGui::Checkbox("Pelvis", &CONFIGBOOL("Legit>LegitBot>AWP>Pelvis"));

                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Heavy")) {
                ImGui::Checkbox("Override", &CONFIGBOOL("Legit>LegitBot>Heavy>Override"));
                ImGui::Text("FOV (x10)");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##FOV", &CONFIGINT("Legit>LegitBot>Heavy>FOV"), 0, 1800);
                ImGui::Text("Smoothing");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Smoothing", &CONFIGINT("Legit>LegitBot>Heavy>Smoothing"), 0, 100);
                ImGui::Checkbox("Recoil Compensation", &CONFIGBOOL("Legit>LegitBot>Heavy>Recoil Compensation"));
                if (CONFIGBOOL("Legit>LegitBot>Heavy>Recoil Compensation")) {
                    ImGui::Text("RCS Amount X");
                    ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                    ImGui::SliderInt("##RCS Amount X", &CONFIGINT("Legit>LegitBot>Heavy>RCS Amount X"), 0, 100);
                    ImGui::Text("RCS Amount Y");
                    ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                    ImGui::SliderInt("##RCS Amount Y", &CONFIGINT("Legit>LegitBot>Heavy>RCS Amount Y"), 0, 100);
                }

                ImGui::Checkbox("Flash Check", &CONFIGBOOL("Legit>LegitBot>Heavy>Flash Check"));
                ImGui::Checkbox("Jump Check", &CONFIGBOOL("Legit>LegitBot>Heavy>Jump Check"));
                ImGui::Checkbox("Enemy Jump Check", &CONFIGBOOL("Legit>LegitBot>Heavy>Enemy Jump Check"));

                ImGui::Text("Hitboxes");
                ImGui::Checkbox("Head", &CONFIGBOOL("Legit>LegitBot>Heavy>Head"));
                ImGui::Checkbox("Chest", &CONFIGBOOL("Legit>LegitBot>Heavy>Chest"));
                ImGui::Checkbox("Stomach", &CONFIGBOOL("Legit>LegitBot>Heavy>Stomach"));
                ImGui::Checkbox("Pelvis", &CONFIGBOOL("Legit>LegitBot>Heavy>Pelvis"));

                ImGui::EndTabItem();
            }
        ImGui::EndTabBar();
        }
        ImGui::EndChild();
    }
    ImGui::SameLine();
    ImGui::BeginChild("Triggerbot", ImVec2(0, 260), true); {
        ImGui::Text("Triggerbot");
        ImGui::Separator();
        if (CONFIGBOOL("Legit>Triggerbot>Triggerbot")) {
            static bool triggerbotKeyToggled = false;
            CustomWidgets::drawKeyBinder("Key", &CONFIGINT("Legit>Triggerbot>Key"), &triggerbotKeyToggled);
            ImGui::SameLine();
        }
        ImGui::Checkbox("Triggerbot", &CONFIGBOOL("Legit>Triggerbot>Triggerbot"));
        if (CONFIGBOOL("Legit>Triggerbot>Triggerbot")) {
            ImGui::Text("Head Hitchance");
            ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
            ImGui::SliderInt("##Head Hitchance", &CONFIGINT("Legit>Triggerbot>Head Hitchance"), 0, 100);

            ImGui::Text("Body Hitchance");
            ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
            ImGui::SliderInt("##Body Hitchance", &CONFIGINT("Legit>Triggerbot>Body Hitchance"), 0, 100);
        }

        ImGui::EndChild();
    }
    //ImGui::SameLine();
    ImGui::BeginChild("Backtrack", ImVec2(0, 260), true); {
        ImGui::Text("Backtrack");
        ImGui::Separator();
        ImGui::Checkbox("Backtrack", &CONFIGBOOL("Legit>Backtrack>Backtrack"));
        if (CONFIGBOOL("Legit>Backtrack>Backtrack")) {
            ImGui::Text("Backtrack Ticks");
            ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
            ImGui::SliderInt("##Backtrack Ticks", &CONFIGINT("Legit>Backtrack>Backtrack Ticks"), 1, 12);
        }
        ImGui::Checkbox("Simple Forwardtracking", &CONFIGBOOL("Legit>Backtrack>Simple Forwardtracking"));
        ImGui::EndChild();
    }
}
