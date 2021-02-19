#include "../menu.hpp"

void Menu::drawLegitTab() {
    ImGui::BeginChild("Aim", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.65f, 260), true); {
        ImGui::Text("Aim");
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
                
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Heavy Pistol")) {
                
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Rifle")) {
                
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Scout")) {
                
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("AWP")) {
                
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Heavy")) {
                
                ImGui::EndTabItem();
            }
        ImGui::EndTabBar();
        }
        ImGui::Separator();
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