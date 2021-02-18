#include "../menu.hpp"
#include <filesystem>
#include "../config.hpp"

void Menu::drawMiscTab() {
    if (ImGui::BeginTabBar("##miscTabs")) {
        if (ImGui::BeginTabItem("Misc")) {
            ImGui::Columns(2, NULL, false);
            ImGui::SetColumnWidth(-1, ImGui::GetWindowContentRegionWidth() * 0.62);
            ImGui::BeginChild("Misc", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.61, ImGui::GetWindowHeight() * 0.85f), true); {
                ImGui::Text("Misc");
                ImGui::Separator();
                ImGui::Checkbox("Developer window", &devWindow);
                ImGui::Checkbox("Disable Watermark", &CONFIGBOOL("Misc>Misc>Misc>Disable Watermark"));
                ImGui::Checkbox("Force square radar", &CONFIGBOOL("Misc>Misc>Misc>Force square radar"));
                ImGui::Checkbox("Rank Revealer", &CONFIGBOOL("Misc>Misc>Misc>Rank Revealer"));

                ImGui::Checkbox("Spectators", &CONFIGBOOL("Misc>Misc>Misc>Spectators"));
                ImGui::Checkbox("Player List", &CONFIGBOOL("Misc>Misc>Misc>Player List"));
                ImGui::Checkbox("Flappy Birb", &CONFIGBOOL("Misc>Misc>Misc>Flappy Birb"));
                ImGui::Checkbox("Auto Accept", &CONFIGBOOL("Misc>Misc>Misc>Auto Accept"));
                ImGui::Checkbox("Auto Defuse", &CONFIGBOOL("Misc>Misc>Misc>Auto Defuse"));
                if (CONFIGBOOL("Misc>Misc>Misc>Auto Defuse")) {
                    ImGui::SameLine();
                    ImGui::Checkbox("Latest Defuse", &CONFIGBOOL("Misc>Misc>Misc>Latest Defuse"));
                }
                ImGui::SameLine();
                ImGui::TextDisabled("?");
                if (ImGui::IsItemHovered())
                    ImGui::SetTooltip("May cause untrusted, use at own risk!");
                ImGui::EndChild();
            }

            ImGui::NextColumn();

            ImGui::BeginChild("Config", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.38, ImGui::GetWindowHeight() * 0.279f), true); {
                ImGui::Text("Config");
                ImGui::Separator();
                if (ImGui::Button("Save")) {
                    Config::save();
                };
                if (ImGui::Button("Load")) {
                    Config::load();            
                };
                ImGui::EndChild();
            }
            ImGui::BeginChild("Clantag", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.38, ImGui::GetWindowHeight() * 0.279f), true); {
                ImGui::Text("Clantag");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::InputText("##clantag-tbox", clantag, IM_ARRAYSIZE(clantag));
                ImGui::Checkbox("Clantag", &CONFIGBOOL("Misc>Misc>Clantag>Clantag"));
                ImGui::Checkbox("Marquee", &CONFIGBOOL("Misc>Misc>Clantag>Clantag Marquee"));
                ImGui::Checkbox("Bee Movie Clantag", &CONFIGBOOL("Misc>Misc>Clantag>Bee Movie Clantag"));
                ImGui::EndChild();
            }
            ImGui::BeginChild("Movement", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.38, ImGui::GetWindowHeight() * 0.279f), true); {
                ImGui::Text("Movement");
                ImGui::Separator();
                ImGui::Checkbox("Auto Hop", &CONFIGBOOL("Misc>Misc>Movement>Auto Hop"));
                ImGui::SliderInt("Auto Hop Hitchance", &CONFIGINT("Misc>Misc>Movement>Auto Hop Hitchance"), 1, 100);
                ImGui::Checkbox("Fast Duck", &CONFIGBOOL("Misc>Misc>Movement>Fast Duck"));
                ImGui::EndChild();
            }
            ImGui::Columns(1);
            ImGui::TextDisabled("Credits!");
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("sekc (ofcourse)\nAll other contributors on GitHub (cristeigabriel, crazily, luk1337 & tango1337)\nand ocornut for his great ImGui UI framework");
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
}
