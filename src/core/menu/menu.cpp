#include "../../includes.hpp"
#include "imgui/imgui.h"
#include <cstdint>
#include <filesystem>
#include <string>

void style() {
    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.06f, 0.06f, 0.06f, 0.98f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border]                 = ImVec4(0.24f, 0.24f, 0.24f, 0.50f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.05f, 0.41f, 0.06f, 0.62f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.13f, 0.84f, 0.15f, 0.40f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.12f, 0.80f, 0.06f, 0.67f);
    colors[ImGuiCol_TitleBg]                = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.16f, 0.29f, 0.48f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.67f, 0.67f, 0.67f, 1.00f);
    colors[ImGuiCol_CheckMark]              = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.46f, 0.46f, 0.46f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
    colors[ImGuiCol_Button]                 = ImVec4(0.12f, 0.50f, 0.04f, 0.62f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.24f, 0.81f, 0.19f, 0.40f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.05f, 0.95f, 0.04f, 0.40f);
    colors[ImGuiCol_Header]                 = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_Separator]              = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.11f, 0.50f, 0.04f, 0.62f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.32f, 0.81f, 0.19f, 0.62f);
    colors[ImGuiCol_TabActive]              = ImVec4(0.20f, 0.75f, 0.15f, 0.62f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
    colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

    ImGui::GetStyle().ScrollbarSize = 8;
    ImGui::GetStyle().ScrollbarRounding = 0;
    ImGui::GetStyle().WindowRounding = 0;
    ImGui::GetStyle().TabRounding = 2;
    ImGui::GetStyle().FrameRounding = 0;
    ImGui::GetStyle().TabRounding = 2;
}

void Menu::onPollEvent(SDL_Event* event, const int result) {
    if (result && ImGui_ImplSDL2_ProcessEvent(event) && Menu::open) {
        event->type = 0;
    }
}

void Menu::onSwapWindow(SDL_Window* window) {
    if (!initialised) {
        gl3wInit();
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplOpenGL3_Init("#version 100");
        ImGui_ImplSDL2_InitForOpenGL(window, nullptr);
        initialised = true;
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window);

    ImGuiIO& io = ImGui::GetIO();
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    io.DisplaySize = ImVec2((float)w, (float)h);

    ImGui::NewFrame();

    Menu::drawOverlay(ImGui::GetBackgroundDrawList());
    if (Menu::open) {
        io.MouseDrawCursor = true; // TODO: find workaround at some point because ugly
        Menu::drawMenu();
        if (devWindow) {
            drawDevWindow();
        }
        if (demoWindow) {
            ImGui::ShowDemoWindow();
        }
    }
    else {
        io.MouseDrawCursor = false;
    }


    if (ImGui::IsKeyPressed(SDL_SCANCODE_INSERT, false)) {
        Menu::open = !Menu::open;
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Menu::drawDevWindow() {
    ImGui::SetNextWindowSize(ImVec2{500, 700});
    ImGui::Begin("devwindow", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    ImGui::Text("developer");
    ImGui::Separator();

    ImGui::Checkbox("Demo window", &demoWindow);

    if (ImGui::TreeNode("Interfaces")) {
        if (ImGui::TreeNode("Globals")) {
            ImGui::Text("realtime: %f", Interfaces::globals->realtime);
            ImGui::Text("framecount: %d", Interfaces::globals->framecount);
            ImGui::Text("absoluteframetime: %f", Interfaces::globals->absoluteframetime);
            ImGui::Text("absoluteframestarttimestddev: %f", Interfaces::globals->absoluteframestarttimestddev);
            ImGui::Text("curtime: %f", Interfaces::globals->curtime);
            ImGui::Text("frametime: %f", Interfaces::globals->frametime);
            ImGui::Text("maxClients: %d", Interfaces::globals->maxClients);
            ImGui::Text("tickcount: %d", Interfaces::globals->tickcount);
            ImGui::Text("interval_per_tick: %f", Interfaces::globals->interval_per_tick);
            ImGui::Text("interpolation_amount: %f", Interfaces::globals->interpolation_amount);
            ImGui::Text("simTicksThisFrame: %d", Interfaces::globals->simTicksThisFrame);
            ImGui::Text("network_protocol: %d", Interfaces::globals->network_protocol);
            ImGui::Text("m_bClient: %d", Interfaces::globals->m_bClient);
            ImGui::Text("m_bRemoteClient: %d", Interfaces::globals->m_bRemoteClient);
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("Engine Client")) {
            int windowW, windowH;
            Interfaces::engine->GetScreenSize(windowW, windowH);
            ImGui::Text("GetScreenSize: %dx%d", windowW, windowH);
            ImGui::Text("IsInGame: %d", Interfaces::engine->IsInGame());
            ImGui::Text("IsConnected: %d",Interfaces::engine->IsConnected());
            ImGui::TreePop();
        }
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("Netvar testing")) {
        if (ImGui::TreeNode("LocalPlayer")) {
            if (Interfaces::engine->IsInGame()) {
                player* localplayer = (player*)Interfaces::entityList->GetClientEntity(Interfaces::engine->GetLocalPlayer());
                ImGui::Text("dormant: %d", localplayer->dormant());
                ImGui::Text("isPlayer: %d", localplayer->isPlayer());
                ImGui::Text("DT_BasePlayer m_iHealth: %d", localplayer->health());
                ImGui::Text("DT_CSPlayer m_fFlags: %d", localplayer->flags());
                ImGui::Text("DT_BaseEntity m_bSpotted: %d", localplayer->spotted());
                ImGui::Text("DT_BasePlayer m_vecOrigin: %f %f %f", localplayer->origin().x, localplayer->origin().y, localplayer->origin().y);
            }
            ImGui::TreePop();
        }
        ImGui::TreePop();
    }

    ImGui::End();
}

void Menu::drawMenu() {
    style();
    ImGui::SetNextWindowSize(ImVec2{900, 600});
    ImGui::Begin("gamesneeze-linux", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 4));
    ImGui::Text("game"); ImGui::SameLine(); ImGui::PopStyleVar(); 
    if (ImGui::IsItemClicked()) {
        system("xdg-open https://discord.gg/SCHsWHFJMb"); //if it works it works lmao
    }
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("Click for discord!");
    }
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(490, 5)); 
    ImGui::TextColored(ImColor(108, 195, 18, 255), "sneeze");
    if (ImGui::IsItemClicked()) {
        system("xdg-open https://discord.gg/SCHsWHFJMb"); //if it works it works lmao
    }
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("Click for discord!");
    }
    ImGui::SameLine(); 
    ImGui::PopStyleVar();

    auto bWidth = ImVec2(80, 18);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(2, 5));
    if (ImGui::Button("Legit", bWidth)) {
        Menu::tabSelected = 0;
    } ImGui::SameLine(); 
    if (ImGui::Button("Rage", bWidth)) {
        Menu::tabSelected = 1;
    } ImGui::SameLine(); 
    if (ImGui::Button("Visuals", bWidth)) {
        Menu::tabSelected = 2;
    } ImGui::SameLine(); 
    if (ImGui::Button("Misc", bWidth)) {
        Menu::tabSelected = 3;
    }
    ImGui::PopStyleVar();

    ImGui::Separator();

    switch(tabSelected) {
        case 0: {
            ImGui::Text("Legit"); break;
        }
        case 1: {
            ImGui::Text("Rage"); break;
        }
        case 2: {
            ImGui::Text("Visuals"); break;
            ImGui::BeginChild("Enemies", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.65f, 260), true); {

                ImGui::EndChild();
            }
        }
        case 3: {
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(800, 4));
            ImGui::Text("Misc");
            ImGui::SameLine();ImGui::PopStyleVar(); 
            ImGui::TextDisabled("Credits!");
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("sekc (ofcourse)\nAll other contributors on GitHub (sadly none as of right now ;'( )\nand ocornut for his great ImGui UI framework");

            ImGui::BeginChild("Trolling", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.65f, 260), true); {
                ImGui::Text("Trolling");
                ImGui::Separator();
                ImGui::Text("Radio Exploit");
                static char victim[128] = "";
                ImGui::InputText("Victim's name", victim, IM_ARRAYSIZE(victim));
                static char message[128] = "";
                ImGui::InputText("Message##tbox", message, IM_ARRAYSIZE(message));
                static char skinName[128] = "★ M9 Bayonet | Doppler";
                ImGui::InputText("Skin/Weapon##tbox", skinName, IM_ARRAYSIZE(skinName));
                ImGui::Text("Send fake: ");
                ImGui::SameLine();
                if (ImGui::Button("Message##btn")) {
                    Interfaces::engine->ExecuteClientCmd((std::string("playerchatwheel . \"Cheer!  ") + victim + " :""\x01"" " + message + "\"").c_str());
                }
                ImGui::SameLine();
                if (ImGui::Button("Server")) {
                    Interfaces::engine->ExecuteClientCmd((std::string("playerchatwheel . \"Cheer!  ""\x01""Console: ") + message + "\"").c_str());
                }
                ImGui::SameLine();
                if (ImGui::Button("VAC")) {
                    Interfaces::engine->ExecuteClientCmd((std::string("playerchatwheel . \"Cheer!  ""\x02""") + victim + " has been permanently banned from official CS:GO servers.\"").c_str());
                }
                ImGui::SameLine();
                if (ImGui::Button("Kick")) {
                    Interfaces::engine->ExecuteClientCmd((std::string("playerchatwheel . \"Cheer!  ""\x01""Player ") + victim + " left the game (Kicked from the session)\"").c_str());
                }
                ImGui::SameLine();
                if (ImGui::Button("Unbox")) {
                    Interfaces::engine->ExecuteClientCmd((std::string("playerchatwheel . \"Cheer!  ""\x0B""") + victim + """\x01"" has opened a container and found:""\x02"" " + skinName + "\"").c_str());
                }
                ImGui::SameLine();
                ImGui::TextDisabled("?");
                if (ImGui::IsItemHovered())
                    ImGui::SetTooltip("Sends a fake message into the chat via a radio message that uses\nchars to create a newline and change colours (pastebin.com/pZvCnGaC),\nyou can do this legit too via the 'playerchatwheel . \"\"' command!\n\nOnly works if you are alive and only teammates can see the message :(");

                ImGui::EndChild();
            }
            ImGui::SameLine();
            ImGui::BeginChild("Config", ImVec2(0, 260), true); {
                ImGui::Text("Config");
                ImGui::Separator();
                ImGui::EndChild();
            }
            ImGui::BeginChild("Movement", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.35f, 260), true); {
                ImGui::Text("Movement");
                ImGui::Separator();
                ImGui::EndChild();
            }
            ImGui::SameLine();
            ImGui::BeginChild("Misc", ImVec2(0, 260), true); {
                ImGui::Text("Misc");
                ImGui::Separator();
                ImGui::Checkbox("Developer window", &devWindow);
                ImGui::EndChild();
            }
            break;
        }
    }

    ImGui::End();
}