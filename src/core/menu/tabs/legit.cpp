#include "../menu.hpp"

void Menu::drawLegitTab() {
    ImGui::BeginChild("Aim", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.65f, 260), true); {
        ImGui::Text("Aim");
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