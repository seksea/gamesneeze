#include "../menu.hpp"
#include <filesystem>
#include "../config.hpp"

void Menu::drawMiscTab() {
    if (ImGui::BeginTabBar("##miscTabs")) {
        if (ImGui::BeginTabItem("Misc")) {
            ImGui::Columns(2, NULL, false);
            ImGui::SetColumnWidth(-1, ImGui::GetWindowContentRegionWidth() * 0.62);
            ImGui::BeginChild("Misc", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.61, ImGui::GetWindowHeight() * 0.64f), true); {
                ImGui::Text("Misc");
                ImGui::Separator();
                ImGui::Checkbox("Developer window", &devWindow);
                ImGui::Checkbox("Disable Watermark", &CONFIGBOOL("Misc>Misc>Misc>Disable Watermark"));
                ImGui::Checkbox("Force square radar", &CONFIGBOOL("Misc>Misc>Misc>Force square radar"));
                ImGui::Checkbox("Rank Revealer", &CONFIGBOOL("Misc>Misc>Misc>Rank Revealer"));

                ImGui::Checkbox("Spectators", &CONFIGBOOL("Misc>Misc>Misc>Spectators"));
                ImGui::Checkbox("Player List", &CONFIGBOOL("Misc>Misc>Misc>Player List"));
                if (CONFIGBOOL("Misc>Misc>Misc>Player List")) {
                    ImGui::SameLine();
                    ImGui::Checkbox("Only When Menu Open", &CONFIGBOOL("Misc>Misc>Misc>Player List Only When Menu Open"));
                }
                ImGui::Checkbox("Flappy Birb", &CONFIGBOOL("Misc>Misc>Misc>Flappy Birb"));
                ImGui::Checkbox("Auto Accept", &CONFIGBOOL("Misc>Misc>Misc>Auto Accept"));
                ImGui::Checkbox("Auto Defuse", &CONFIGBOOL("Misc>Misc>Misc>Auto Defuse"));
                if (CONFIGBOOL("Misc>Misc>Misc>Auto Defuse")) {
                    ImGui::SameLine();
                    ImGui::Checkbox("Latest Defuse", &CONFIGBOOL("Misc>Misc>Misc>Latest Defuse"));
                }
                ImGui::Checkbox("Chat Filter Bypass", &CONFIGBOOL("Misc>Misc>Misc>Chat Filter Bypass"));
                if (CONFIGBOOL("Misc>Misc>Misc>Use Spam")) {
                    static bool toggled = false;
                    Menu::CustomWidgets::drawKeyBinder("Key", &CONFIGINT("Misc>Misc>Misc>Use Spam Key"), &toggled);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Use Spam", &CONFIGBOOL("Misc>Misc>Misc>Use Spam"));
                ImGui::Checkbox("Disable Setting Cvars", &CONFIGBOOL("Misc>Misc>Misc>Disable Setting Cvars"));
                ImGui::Checkbox("Disable Post Processing", &CONFIGBOOL("Misc>Misc>Misc>Disable Post Processing"));
                ImGui::EndChild();
            }

            ImGui::BeginChild("Hitmarkers", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.61, ImGui::GetWindowHeight() * 0.21f), true); {
                ImGui::Text("Hitmarkers");
                ImGui::Separator();
                ImGui::Checkbox("Hitlogs", &CONFIGBOOL("Misc>Misc>Hitmarkers>Hitlogs"));
                ImGui::Checkbox("Hitmarkers", &CONFIGBOOL("Misc>Misc>Hitmarkers>Hitmarkers"));
                ImGui::Checkbox("Hitsound", &CONFIGBOOL("Misc>Misc>Hitmarkers>Hitsound"));
                ImGui::Checkbox("Damage Markers", &CONFIGBOOL("Misc>Misc>Hitmarkers>Damage Markers"));
                ImGui::EndChild();
            }

            ImGui::NextColumn();

            ImGui::BeginChild("Config", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.38, ImGui::GetWindowHeight() * 0.307), true); {
                ImGui::Text("Config");
                ImGui::Separator();

                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::ListBoxHeader("##configlist-lbox", ImVec2(0, 100));
                for (std::string file : Config::cfgFiles) {
                    if (ImGui::Button(file.c_str())) {
                        strcpy(Config::configFileName, file.c_str());
                    }
                }
                ImGui::ListBoxFooter();

                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::InputText("##configfile-tbox", Config::configFileName, IM_ARRAYSIZE(Config::configFileName));
                if (ImGui::Button("Save", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.315, 0))) {
                    Config::save();
                }; ImGui::SameLine();
                if (ImGui::Button("Load", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.315, 0))) {
                    Config::load();
                    FULLUPDATE();
                }; ImGui::SameLine();
                if (ImGui::Button("Remove", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.315, 0))) {
                    Config::remove();
                };
                ImGui::EndChild();
            }

            ImGui::BeginChild("Clantag", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.38, ImGui::GetWindowHeight() * 0.21f), true); {
                ImGui::Text("Clantag");
                ImGui::Separator();
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::InputText("##clantag-tbox", clantag, IM_ARRAYSIZE(clantag));
                ImGui::Checkbox("Clantag", &CONFIGBOOL("Misc>Misc>Clantag>Clantag"));
                ImGui::Checkbox("Marquee", &CONFIGBOOL("Misc>Misc>Clantag>Clantag Marquee"));
                ImGui::Checkbox("Bee Movie Clantag", &CONFIGBOOL("Misc>Misc>Clantag>Bee Movie Clantag"));
                ImGui::EndChild();
            }

            ImGui::BeginChild("Movement", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.38, ImGui::GetWindowHeight() * 0.326f), true); {
                ImGui::Text("Movement");
                ImGui::Separator();
                ImGui::Checkbox("Auto Hop", &CONFIGBOOL("Misc>Misc>Movement>Auto Hop"));
                ImGui::Checkbox("Humanised Bhop", &CONFIGBOOL("Misc>Misc>Movement>Humanised Bhop"));
                if (CONFIGBOOL("Misc>Misc>Movement>Humanised Bhop")) {
                    ImGui::Text("Bhop Hitchance");
                    ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                    ImGui::SliderInt("##Bhop Hitchance", &CONFIGINT("Misc>Misc>Movement>Bhop Hitchance"), 0, 100);
                    ImGui::Text("Bhop Max Misses");
                    ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                    ImGui::SliderInt("##Bhop Max Misses", &CONFIGINT("Misc>Misc>Movement>Bhop Max Misses"), 0, 16);
                    ImGui::Text("Bhop Max Hops Hit");
                    ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                    ImGui::SliderInt("##Bhop Max Hops Hit", &CONFIGINT("Misc>Misc>Movement>Bhop Max Hops Hit"), 0, 16);
                }
                if (CONFIGBOOL("Misc>Misc>Movement>Edge Jump")) {
                    static bool toggled = false;
                    Menu::CustomWidgets::drawKeyBinder("Key", &CONFIGINT("Misc>Misc>Movement>Edge Jump Key"), &toggled);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Edge Jump", &CONFIGBOOL("Misc>Misc>Movement>Edge Jump"));
                if (CONFIGBOOL("Misc>Misc>Movement>JumpBug")) {
                    static bool toggled = false;
                    Menu::CustomWidgets::drawKeyBinder("Key", &CONFIGINT("Misc>Misc>Movement>JumpBug Key"), &toggled);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("JumpBug", &CONFIGBOOL("Misc>Misc>Movement>JumpBug"));
                if (CONFIGBOOL("Misc>Misc>Movement>EdgeBug")) {
                    static bool toggled = false;
                    Menu::CustomWidgets::drawKeyBinder("Key", &CONFIGINT("Misc>Misc>Movement>EdgeBug Key"), &toggled);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("EdgeBug", &CONFIGBOOL("Misc>Misc>Movement>EdgeBug"));
                ImGui::Checkbox("Fast Duck", &CONFIGBOOL("Misc>Misc>Movement>Fast Duck"));
                ImGui::SameLine();
                ImGui::TextDisabled("?");
                if (ImGui::IsItemHovered())
                    ImGui::SetTooltip("May cause untrusted, use at own risk!");
                ImGui::EndChild();
            }
            ImGui::Columns(1);
            ImGui::TextDisabled("Credits!");
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("sekc (of course)\nAll other contributors on GitHub (xXx-sans-xXx, luk1337, cristeigabriel, crazily, dave (@dweee), keenan, u2ooS, tango1337, nigma1337, vampur, jovvik, all and any other contributors, and allbombson)\nand ocornut for his great ImGui UI framework");
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Skins")) {
            static ItemIndex curWeaponSelected = ItemIndex::WEAPON_AK47;
            if (ImGui::BeginCombo("Weapon", itemIndexMap.at(curWeaponSelected))) {
                for (auto item : itemIndexMap) {
                    if (item.first != ItemIndex::INVALID) {
                        ImGui::PushID(item.second);
                        const bool is_selected = (itemIndexMap.at(curWeaponSelected) == item.second);
                        if (ImGui::Selectable(item.second, is_selected)) {
                            curWeaponSelected = item.first;
                            FULLUPDATE();
                        }
                        ImGui::PopID();
                    }
                }
                ImGui::EndCombo();
            }
            if (curWeaponSelected != ItemIndex::INVALID) {
                char* buf = new char[256];
                snprintf(buf, 256, "Misc>Skins>Skins>%s>PaintKit", itemIndexMap.at(curWeaponSelected));
                if (ImGui::DragInt("PaintKit", &CONFIGINT(buf))) {
                    FULLUPDATE();
                }

                char* buf2 = new char[256];
                snprintf(buf2, 256, "Misc>Skins>Skins>%s>Wear", itemIndexMap.at(curWeaponSelected));
                if (ImGui::SliderInt("Wear", &CONFIGINT(buf2), 0, 100)) {
                    FULLUPDATE();
                }

                char* buf3 = new char[256];
                snprintf(buf3, 256, "Misc>Skins>Skins>%s>StatTrack", itemIndexMap.at(curWeaponSelected));
                if (ImGui::DragInt("StatTrack", &CONFIGINT(buf3))) {
                    FULLUPDATE();
                }
            }
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
}
