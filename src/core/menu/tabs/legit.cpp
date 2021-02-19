#include "../menu.hpp"

void Menu::drawLegitTab() {
    ImGui::BeginChild("Aim", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.65f, 260), true); {
        ImGui::Text("Aim");
        ImGui::Separator();
        if (ImGui::BeginTabBar("Aim Weapons Tabbar")) {
            if (ImGui::BeginTabItem("Default")) {
                static bool keybindToggled;
                Menu::CustomWidgets::drawKeyBinder("Key", &CONFIGINT("Legit>LegitBot>Default>Key"), &keybindToggled);
                ImGui::SameLine();
                ImGui::Checkbox("Always On", &CONFIGBOOL("Legit>LegitBot>Default>Always on"));
                ImGui::Text("FOV (x10)");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##FOV", &CONFIGINT("Legit>LegitBot>Default>FOV"), 1, 1800);
                ImGui::Text("Smoothing");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Smoothing", &CONFIGINT("Legit>LegitBot>Default>Smoothing"), 0, 100);
                ImGui::Checkbox("Recoil Compensation", &CONFIGBOOL("Legit>LegitBot>Default>Recoil Compensation"));

                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Pistol")) {
                ImGui::Checkbox("Override", &CONFIGBOOL("Legit>LegitBot>Pistol>Override"));
                ImGui::Text("FOV (x10)");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##FOV", &CONFIGINT("Legit>LegitBot>Pistol>FOV"), 1, 1800);
                ImGui::Text("Smoothing");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Smoothing", &CONFIGINT("Legit>LegitBot>Pistol>Smoothing"), 0, 100);
                
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Heavy Pistol")) {
                ImGui::Checkbox("Override", &CONFIGBOOL("Legit>LegitBot>Heavy Pistol>Override"));
                ImGui::Text("FOV (x10)");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##FOV", &CONFIGINT("Legit>LegitBot>Heavy Pistol>FOV"), 1, 1800);
                ImGui::Text("Smoothing");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Smoothing", &CONFIGINT("Legit>LegitBot>Heavy Pistol>Smoothing"), 0, 100);
                
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Rifle")) {
                ImGui::Checkbox("Override", &CONFIGBOOL("Legit>LegitBot>Rifle>Override"));
                ImGui::Text("FOV (x10)");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##FOV", &CONFIGINT("Legit>LegitBot>Rifle>FOV"), 1, 1800);
                ImGui::Text("Smoothing");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Smoothing", &CONFIGINT("Legit>LegitBot>Rifle>Smoothing"), 0, 100);
                ImGui::Checkbox("Recoil Compensation", &CONFIGBOOL("Legit>LegitBot>Rifle>Recoil Compensation"));
                
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("SMG")) {
                ImGui::Checkbox("Override", &CONFIGBOOL("Legit>LegitBot>SMG>Override"));
                ImGui::Text("FOV (x10)");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##FOV", &CONFIGINT("Legit>LegitBot>SMG>FOV"), 1, 1800);
                ImGui::Text("Smoothing");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Smoothing", &CONFIGINT("Legit>LegitBot>SMG>Smoothing"), 0, 100);
                ImGui::Checkbox("Recoil Compensation", &CONFIGBOOL("Legit>LegitBot>SMG>Recoil Compensation"));
                
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Scout")) {
                ImGui::Checkbox("Override", &CONFIGBOOL("Legit>LegitBot>Scout>Override"));
                ImGui::Text("FOV (x10)");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##FOV", &CONFIGINT("Legit>LegitBot>Scout>FOV"), 1, 1800);
                ImGui::Text("Smoothing");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Smoothing", &CONFIGINT("Legit>LegitBot>Scout>Smoothing"), 0, 100);
                
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("AWP")) {
                ImGui::Checkbox("Override", &CONFIGBOOL("Legit>LegitBot>AWP>Override"));
                ImGui::Text("FOV (x10)");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##FOV", &CONFIGINT("Legit>LegitBot>AWP>FOV"), 1, 1800);
                ImGui::Text("Smoothing");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Smoothing", &CONFIGINT("Legit>LegitBot>AWP>Smoothing"), 0, 100);
                
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Heavy")) {
                ImGui::Checkbox("Override", &CONFIGBOOL("Legit>LegitBot>Heavy>Override"));
                ImGui::Text("FOV (x10)");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##FOV", &CONFIGINT("Legit>LegitBot>Heavy>FOV"), 1, 1800);
                ImGui::Text("Smoothing");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Smoothing", &CONFIGINT("Legit>LegitBot>Heavy>Smoothing"), 0, 100);
                ImGui::Checkbox("Recoil Compensation", &CONFIGBOOL("Legit>LegitBot>Heavy>Recoil Compensation"));
                
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
        ImGui::SameLine();
        ImGui::TextDisabled("?");
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Immensely simple, just checks m_iCrosshairId kekw, in future will move to traceray");
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
        ImGui::EndChild();
    }
}