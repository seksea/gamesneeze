#include "../menu.hpp"

void Menu::drawLegitTab() {
    ImGui::Text("Legit");
    ImGui::BeginChild("Aim", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.65f, 253), true); {
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
}