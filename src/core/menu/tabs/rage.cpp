#include "../menu.hpp"

const char* antiAimTypes[] = {"None", "Static", "Jitter", "Fake Jitter", "Real Jitter", "SpingBot (p100)"};

void Menu::drawRageTab() {
    ImGui::Checkbox("Enabled", &CONFIGBOOL("Rage>Enabled"));
    ImGui::SameLine();
    ImGui::TextDisabled("?");
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("Ragebot is in incredibly early development so don't expect much right now. It currently \n doesnt do any kind of bullet sim (no awall/mindmg) so you have to click yourself and headbone is forced");
    ImGui::Separator();

    ImGui::BeginChild("Rage", ImVec2((ImGui::GetWindowContentRegionWidth()/2) - 4, 520), true); {
        ImGui::Text("RageBot");
        ImGui::Separator();
        if (ImGui::BeginTabBar("Weapons Tabbar")) {
            if (ImGui::BeginTabItem("Default")) {
                ImGui::Checkbox("Resolver", &CONFIGBOOL("Rage>RageBot>Default>Resolver"));
                ImGui::Checkbox("Force Baim if health < X", &CONFIGBOOL("Rage>RageBot>Default>ForceBaim"));
                if(CONFIGBOOL("Rage>RageBot>Default>ForceBaim")) {
                    ImGui::Text("Health");
                    ImGui::SliderInt("##HEALTH", &CONFIGINT("Rage>RageBot>Default>ForceBaimValue"), 1, 100);
                }
                ImGui::Text("FOV (x10)");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##FOV", &CONFIGINT("Rage>RageBot>Default>FOV"), 0, 1800);
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
        ImGui::EndChild();
    }
    ImGui::SameLine();
    ImGui::BeginChild("Anti-Aim", ImVec2((ImGui::GetWindowContentRegionWidth()/2) - 4, 520), true); {
        ImGui::Text("Anti-Aim");
        ImGui::Separator();
        
        ImGui::Text("Type");
        ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
        ImGui::Combo("##Type", &CONFIGINT("Rage>AntiAim>Type"), antiAimTypes, IM_ARRAYSIZE(antiAimTypes));

        if (CONFIGINT("Rage>AntiAim>Type")) {
            ImGui::Text("Pitch");
            ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
            ImGui::SliderInt("##Pitch", &CONFIGINT("Rage>AntiAim>Pitch"), -89, 89);

            ImGui::Text("Yaw Offset");
            ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
            ImGui::SliderInt("##Offset", &CONFIGINT("Rage>AntiAim>Offset"), 0, 360);

            ImGui::Text("FakeLag");
            ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
            ImGui::SliderInt("##FakeLag", &CONFIGINT("Rage>AntiAim>FakeLag"), 0, 16);
        }

        if (CONFIGINT("Rage>AntiAim>Type") == 1) { // Static
            ImGui::Text("Desync");
            ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
            ImGui::SliderInt("##Desync", &CONFIGINT("Rage>AntiAim>Static>Desync"), -60, 60);
        }

        if (CONFIGINT("Rage>AntiAim>Type") == 2) { // Jitter
            ImGui::Text("Desync");
            ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
            ImGui::SliderInt("##Desync", &CONFIGINT("Rage>AntiAim>Jitter>Desync"), -60, 60);

            ImGui::Text("Jitter Amount");
            ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
            ImGui::SliderInt("##Jitter Amount", &CONFIGINT("Rage>AntiAim>Jitter>Jitter Amount"), 0, 180);

            ImGui::Text("Jitter Delay");
            ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
            ImGui::SliderInt("##Jitter Delay", &CONFIGINT("Rage>AntiAim>Jitter>Jitter Delay"), 1, 256);

            ImGui::Checkbox("Random", &CONFIGBOOL("Rage>AntiAim>Jitter>Random"));
            if (CONFIGBOOL("Rage>AntiAim>Jitter>Random")) {
                ImGui::Text("Random Min");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Random Min", &CONFIGINT("Rage>AntiAim>Jitter>Random Min"), 0, 180);

                ImGui::Text("Random Max");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Random Max", &CONFIGINT("Rage>AntiAim>Jitter>Random Max"), 0, 180);
            }
        }

        if (CONFIGINT("Rage>AntiAim>Type") == 3) { // Fake Jitter
            ImGui::Text("Jitter Amount");
            ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
            ImGui::SliderInt("##Jitter Amount", &CONFIGINT("Rage>AntiAim>Fake Jitter>Jitter Amount"), 0, 60);

            ImGui::Text("Jitter Delay");
            ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
            ImGui::SliderInt("##Jitter Delay", &CONFIGINT("Rage>AntiAim>Fake Jitter>Jitter Delay"), 1, 256);

            ImGui::Checkbox("Random", &CONFIGBOOL("Rage>AntiAim>Fake Jitter>Random"));
            if (CONFIGBOOL("Rage>AntiAim>Fake Jitter>Random")) {
                ImGui::Text("Random Min");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Random Min", &CONFIGINT("Rage>AntiAim>Fake Jitter>Random Min"), 0, 60);

                ImGui::Text("Random Max");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Random Max", &CONFIGINT("Rage>AntiAim>Fake Jitter>Random Max"), 0, 60);
            }
        }

        if (CONFIGINT("Rage>AntiAim>Type") == 4) { // Real Jitter
            ImGui::Text("Jitter Amount");
            ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
            ImGui::SliderInt("##Jitter Amount", &CONFIGINT("Rage>AntiAim>Real Jitter>Jitter Amount"), 0, 60);

            ImGui::Text("Jitter Delay");
            ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
            ImGui::SliderInt("##Jitter Delay", &CONFIGINT("Rage>AntiAim>Real Jitter>Jitter Delay"), 1, 256);

            ImGui::Checkbox("Random", &CONFIGBOOL("Rage>AntiAim>Fake Jitter>Random"));
            if (CONFIGBOOL("Rage>AntiAim>Real Jitter>Random")) {
                ImGui::Text("Random Min");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Random Min", &CONFIGINT("Rage>AntiAim>Real Jitter>Random Min"), 0, 60);

                ImGui::Text("Random Max");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Random Max", &CONFIGINT("Rage>AntiAim>Real Jitter>Random Max"), 0, 60);
            }
        }

        if (CONFIGINT("Rage>AntiAim>Type") == 5) { // Sping
            ImGui::Text("Desync");
            ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
            ImGui::SliderInt("##Desync", &CONFIGINT("Rage>AntiAim>Spin>Desync"), -60, 60);
        }
        ImGui::Checkbox("Slow Walk",&CONFIGBOOL("Rage>AntiAim>Slow Walk"));
        ImGui::SliderInt("Slow Walk Speed (%)", &CONFIGINT("Rage>AntiAim>Slow Walk Speed"), 0, 255);
        ImGui::EndChild();
    }
}