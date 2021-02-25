#include "../menu.hpp"

void Menu::drawRageTab() {
    ImGui::Checkbox("Enabled", &CONFIGBOOL("Rage>Enabled"));
    ImGui::SameLine();
    ImGui::TextDisabled("?");
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("Ragebot is in incredibly early development so don't expect much right now. It currently \n doesnt have AA, doesnt do any kind of bullet sim (no awall/mindmg), and doesnt have a resolver");
    ImGui::Separator();

    ImGui::BeginChild("Rage", ImVec2(ImGui::GetWindowContentRegionWidth(), 260), true); {
        ImGui::Text("RageBot");
        ImGui::Separator();
        if (ImGui::BeginTabBar("Weapons Tabbar")) {
            if (ImGui::BeginTabItem("Default")) {
                ImGui::Text("FOV (x10)");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##FOV", &CONFIGINT("Rage>RageBot>Default>FOV"), 0, 1800);

                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
        ImGui::EndChild();
    }
    ImGui::BeginChild("Anti-Aim", ImVec2(ImGui::GetWindowContentRegionWidth(), 260), true); {
        ImGui::Text("Anti-Aim");
        ImGui::Separator();

        ImGui::EndChild();
    }
}