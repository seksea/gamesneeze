#include "../menu.hpp"
#include <sstream>

void hitboxSelectBox(const char* configVarName) {
    ImGui::Text("Hitboxes");
    ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());

    int curSelected = CONFIGINT(configVarName);

    std::stringstream selectedHitboxes;
    selectedHitboxes << (curSelected & (int)HitBoxes::HEAD ? "Head, " : "")
                     << (curSelected & (int)HitBoxes::NECK ? "Neck, " : "")
                     << (curSelected & (int)HitBoxes::CHEST ? "Chest, " : "")
                     << (curSelected & (int)HitBoxes::STOMACH ? "Stomach, " : "")
                     << (curSelected & (int)HitBoxes::PELVIS ? "Pelvis, " : "");

    if (ImGui::BeginCombo("##HitBoxes", selectedHitboxes.str().c_str())) {

        if (ImGui::Selectable("Head", curSelected & (int)HitBoxes::HEAD, ImGuiSelectableFlags_DontClosePopups))
            CONFIGINT(configVarName) ^= (int)HitBoxes::HEAD;

        if (ImGui::Selectable("Neck", curSelected & (int)HitBoxes::NECK, ImGuiSelectableFlags_DontClosePopups))
            CONFIGINT(configVarName) ^= (int)HitBoxes::NECK;

        if (ImGui::Selectable("Chest", curSelected & (int)HitBoxes::CHEST, ImGuiSelectableFlags_DontClosePopups))
            CONFIGINT(configVarName) ^= (int)HitBoxes::CHEST;

        if (ImGui::Selectable("Stomach", curSelected & (int)HitBoxes::STOMACH, ImGuiSelectableFlags_DontClosePopups))
            CONFIGINT(configVarName) ^= (int)HitBoxes::STOMACH;

        if (ImGui::Selectable("Pelvis", curSelected & (int)HitBoxes::PELVIS, ImGuiSelectableFlags_DontClosePopups))
            CONFIGINT(configVarName) ^= (int)HitBoxes::PELVIS;

        ImGui::EndCombo();
    }
}

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
                hitboxSelectBox("Legit>LegitBot>Default>Hitboxes");
                ImGui::Text("FOV (x10)");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##FOV", &CONFIGINT("Legit>LegitBot>Default>FOV"), 0, 1800);
                ImGui::Text("Smoothing");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Smoothing", &CONFIGINT("Legit>LegitBot>Default>Smoothing"), 0, 100);
                ImGui::Checkbox("Recoil Compensation", &CONFIGBOOL("Legit>LegitBot>Default>Recoil Compensation"));
                ImGui::Checkbox("Aim While Blind", &CONFIGBOOL("Legit>LegitBot>Default>Aim While Blind"));


                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Pistol")) {
                ImGui::Checkbox("Override", &CONFIGBOOL("Legit>LegitBot>Pistol>Override"));
                hitboxSelectBox("Legit>LegitBot>Pistol>Hitboxes");
                ImGui::Text("FOV (x10)");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##FOV", &CONFIGINT("Legit>LegitBot>Pistol>FOV"), 0, 1800);
                ImGui::Text("Smoothing");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Smoothing", &CONFIGINT("Legit>LegitBot>Pistol>Smoothing"), 0, 100);
                ImGui::Checkbox("Aim While Blind", &CONFIGBOOL("Legit>LegitBot>Pistol>Aim While Blind"));

                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Heavy Pistol")) {
                ImGui::Checkbox("Override", &CONFIGBOOL("Legit>LegitBot>Heavy Pistol>Override"));
                hitboxSelectBox("Legit>LegitBot>Heavy Pistol>Hitboxes");
                ImGui::Text("FOV (x10)");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##FOV", &CONFIGINT("Legit>LegitBot>Heavy Pistol>FOV"), 0, 1800);
                ImGui::Text("Smoothing");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Smoothing", &CONFIGINT("Legit>LegitBot>Heavy Pistol>Smoothing"), 0, 100);
                ImGui::Checkbox("Aim While Blind", &CONFIGBOOL("Legit>LegitBot>Heavy Pistol>Aim While Blind"));

                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Rifle")) {
                ImGui::Checkbox("Override", &CONFIGBOOL("Legit>LegitBot>Rifle>Override"));
                hitboxSelectBox("Legit>LegitBot>Rifle>Hitboxes");
                ImGui::Text("FOV (x10)");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##FOV", &CONFIGINT("Legit>LegitBot>Rifle>FOV"), 0, 1800);
                ImGui::Text("Smoothing");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Smoothing", &CONFIGINT("Legit>LegitBot>Rifle>Smoothing"), 0, 100);
                ImGui::Checkbox("Recoil Compensation", &CONFIGBOOL("Legit>LegitBot>Rifle>Recoil Compensation"));
                ImGui::Checkbox("Aim While Blind", &CONFIGBOOL("Legit>LegitBot>Rifle>Aim While Blind"));

                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("SMG")) {
                ImGui::Checkbox("Override", &CONFIGBOOL("Legit>LegitBot>SMG>Override"));
                hitboxSelectBox("Legit>LegitBot>SMG>Hitboxes");
                ImGui::Text("FOV (x10)");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##FOV", &CONFIGINT("Legit>LegitBot>SMG>FOV"), 0, 1800);
                ImGui::Text("Smoothing");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Smoothing", &CONFIGINT("Legit>LegitBot>SMG>Smoothing"), 0, 100);
                ImGui::Checkbox("Recoil Compensation", &CONFIGBOOL("Legit>LegitBot>SMG>Recoil Compensation"));
                ImGui::Checkbox("Aim While Blind", &CONFIGBOOL("Legit>LegitBot>SMG>Aim While Blind"));

                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Scout")) {
                ImGui::Checkbox("Override", &CONFIGBOOL("Legit>LegitBot>Scout>Override"));
                hitboxSelectBox("Legit>LegitBot>Scout>Hitboxes");
                ImGui::Text("FOV (x10)");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##FOV", &CONFIGINT("Legit>LegitBot>Scout>FOV"), 0, 1800);
                ImGui::Text("Smoothing");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Smoothing", &CONFIGINT("Legit>LegitBot>Scout>Smoothing"), 0, 100);
                ImGui::Checkbox("Aim While Blind", &CONFIGBOOL("Legit>LegitBot>Scout>Aim While Blind"));

                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("AWP")) {
                ImGui::Checkbox("Override", &CONFIGBOOL("Legit>LegitBot>AWP>Override"));
                hitboxSelectBox("Legit>LegitBot>AWP>Hitboxes");
                ImGui::Text("FOV (x10)");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##FOV", &CONFIGINT("Legit>LegitBot>AWP>FOV"), 0, 1800);
                ImGui::Text("Smoothing");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Smoothing", &CONFIGINT("Legit>LegitBot>AWP>Smoothing"), 0, 100);
                ImGui::Checkbox("Aim While Blind", &CONFIGBOOL("Legit>LegitBot>AWP>Aim While Blind"));

                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Heavy")) {
                ImGui::Checkbox("Override", &CONFIGBOOL("Legit>LegitBot>Heavy>Override"));
                hitboxSelectBox("Legit>LegitBot>Heavy>Hitboxes");
                ImGui::Text("FOV (x10)");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##FOV", &CONFIGINT("Legit>LegitBot>Heavy>FOV"), 0, 1800);
                ImGui::Text("Smoothing");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Smoothing", &CONFIGINT("Legit>LegitBot>Heavy>Smoothing"), 0, 100);
                ImGui::Checkbox("Recoil Compensation", &CONFIGBOOL("Legit>LegitBot>Heavy>Recoil Compensation"));
                ImGui::Checkbox("Aim While Blind", &CONFIGBOOL("Legit>LegitBot>Heavy>Aim While Blind"));

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
