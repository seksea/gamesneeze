#include "../menu.hpp"

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