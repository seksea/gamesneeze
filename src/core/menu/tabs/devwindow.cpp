#include "../menu.hpp"
#include <map>
#include <vector>



std::map<std::string_view, std::vector<RecvProp>> netvars;

uintptr_t getNetvars() {
    for (ClientClass* cur = Interfaces::client->GetAllClasses(); cur; cur = cur->m_pNext) {
        for (int i = 0; i < cur->m_pRecvTable->m_nProps; i++) {
            RecvProp prop = cur->m_pRecvTable->m_pProps[i];
            netvars[cur->m_pRecvTable->m_pNetTableName].push_back(prop);
        }
    }
    return 0;
}

void Menu::drawDevWindow() {
    ImGui::SetNextWindowSize(ImVec2{500, 700});
    ImGui::Begin("devwindow", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    ImGui::Text("developer");
    ImGui::Separator();

    ImGui::Checkbox("Demo window", &demoWindow);
    if (ImGui::Button("Send test notification")) {
        Features::Notifications::addNotification(ImColor(30, 255, 30), "[gs] Test notification! %f", Interfaces::globals->realtime);
    }

    ImGui::Text("Is in dangerzone: %s", strstr(Offsets::getLocalClient(-1)->m_szLevelNameShort, "dz_") ? "true" : "false");

    static bool gotNetvars = false;
    if (!gotNetvars) {
        getNetvars();
        gotNetvars = true;
    }

    if (ImGui::TreeNode("Netvars")) {
        for (auto table : netvars) {
            if (ImGui::TreeNode(table.first.data())) {
                for (auto prop : table.second) {
                    if (ImGui::TreeNode(prop.m_pVarName)) {
                        ImGui::Text("Parent: %s", table.first.data());
                        ImGui::Text("Flags: %x", prop.m_Flags);
                        ImGui::Text("Offset: %x", prop.m_Offset);
                        ImGui::Text("RecvType: %s", prop.m_RecvType == DPT_Int ? "Int" :
                                                    prop.m_RecvType == DPT_Float ? "Float" :
                                                    prop.m_RecvType == DPT_Vector ? "Vector" :
                                                    prop.m_RecvType == DPT_VectorXY ? "VectorXY" :
                                                    prop.m_RecvType == DPT_String ? "String" :
                                                    prop.m_RecvType == DPT_Array ? "Array" :
                                                    prop.m_RecvType == DPT_DataTable ? "DataTable" : "Unknown Type");
                        ImGui::TreePop();
                    }
                }
                ImGui::TreePop();
            }
        }
        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Interfaces")) {
        if (ImGui::TreeNode("Engine")) {
            int windowW, windowH;
            Interfaces::engine->GetScreenSize(windowW, windowH);
            ImGui::Text("GetScreenSize: %dx%d", windowW, windowH);
            ImGui::Text("IsInGame: %d", Interfaces::engine->IsInGame());
            ImGui::Text("IsConnected: %d",Interfaces::engine->IsConnected());
            ImGui::Text("GetLocalPlayer: %d",Interfaces::engine->GetLocalPlayer());
            ImGui::Text("GetMaxClients: %d",Interfaces::engine->GetMaxClients());
            ImGui::Text("IsVoiceRecording: %d",Interfaces::engine->IsVoiceRecording());
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("EntityList")) {
            ImGui::Text("GetHighestEntityIndex: %d", Interfaces::entityList->GetHighestEntityIndex());
            ImGui::TreePop();
        }
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
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("Entities") && Interfaces::engine->IsInGame()) {
        int highest = Interfaces::entityList->GetHighestEntityIndex();
        for (int i = 0; i < highest; i++) {
            Entity* ent = (Entity*)Interfaces::entityList->GetClientEntity(i);
            if (ent && ent->isPlayer()) {
                Player* p = (Player*)ent;
                if (p->health() > 0 && ImGui::TreeNode(std::to_string(i).c_str(), "PLAYER: %d", i)) {
                    ImGui::Text("dormant: %d", p->dormant());
                    ImGui::Text("isPlayer: %d", p->isPlayer());
                    if (ImGui::TreeNode(std::to_string(i+Interfaces::globals->maxClients).c_str(), "Flags")) {
                        int flags = p->flags();
                        ImGui::Text("FL_ONGROUND: %d", (flags & (1<<0)) ? 1 : 0);
                        ImGui::Text("FL_DUCKING: %d", (flags & (1<<1)) ? 1 : 0);
                        ImGui::Text("FL_ANIMDUCKING: %d", (flags & (1<<2)) ? 1 : 0);
                        ImGui::Text("FL_WATERJUMP: %d", (flags & (1<<3)) ? 1 : 0);
                        ImGui::Text("FL_ONTRAIN: %d", (flags & (1<<4)) ? 1 : 0);
                        ImGui::Text("FL_INTRAIN: %d", (flags & (1<<5)) ? 1 : 0);
                        ImGui::Text("FL_FROZEN: %d", (flags & (1<<6)) ? 1 : 0);
                        ImGui::Text("FL_ATCONTROLS: %d", (flags & (1<<7)) ? 1 : 0);
                        ImGui::Text("FL_CLIENT: %d", (flags & (1<<8)) ? 1 : 0);
                        ImGui::Text("FL_FAKECLIENT: %d", (flags & (1<<9)) ? 1 : 0);
                        ImGui::Text("FL_INWATER: %d", (flags & (1<<10)) ? 1 : 0);
                        ImGui::Text("FL_FLY: %d", (flags & (1<<11)) ? 1 : 0);
                        ImGui::Text("FL_SWIM: %d", (flags & (1<<12)) ? 1 : 0);
                        ImGui::Text("FL_CONVEYOR: %d", (flags & (1<<13)) ? 1 : 0);
                        ImGui::Text("FL_NPC: %d", (flags & (1<<14)) ? 1 : 0);
                        ImGui::Text("FL_GODMODE: %d", (flags & (1<<15)) ? 1 : 0);
                        ImGui::Text("FL_NOTARGET: %d", (flags & (1<<16)) ? 1 : 0);
                        ImGui::Text("FL_AIMTARGET: %d", (flags & (1<<17)) ? 1 : 0);
                        ImGui::Text("FL_PARTIALGROUND: %d", (flags & (1<<18)) ? 1 : 0);
                        ImGui::Text("FL_STATICPROP: %d", (flags & (1<<19)) ? 1 : 0);
                        ImGui::Text("FL_GRAPHED: %d", (flags & (1<<20)) ? 1 : 0);
                        ImGui::Text("FL_GRENADE: %d", (flags & (1<<21)) ? 1 : 0);
                        ImGui::Text("FL_STEPMOVEMENT: %d", (flags & (1<<22)) ? 1 : 0);
                        ImGui::Text("FL_DONTTOUCH: %d", (flags & (1<<23)) ? 1 : 0);
                        ImGui::Text("FL_BASEVELOCITY: %d", (flags & (1<<24)) ? 1 : 0);
                        ImGui::Text("FL_WORLDBRUSH: %d", (flags & (1<<25)) ? 1 : 0);
                        ImGui::Text("FL_OBJECT: %d", (flags & (1<<26)) ? 1 : 0);
                        ImGui::Text("FL_KILLME: %d", (flags & (1<<27)) ? 1 : 0);
                        ImGui::Text("FL_ONFIRE: %d", (flags & (1<<28)) ? 1 : 0);
                        ImGui::Text("FL_DISSOLVING: %d", (flags & (1<<29)) ? 1 : 0);
                        ImGui::Text("FL_TRANSRAGDOLL: %d", (flags & (1<<30)) ? 1 : 0);
                        ImGui::Text("FL_UNBLOCKABLE_BY_PLAYER: %d", (flags & (1<<31)) ? 1 : 0);
                        ImGui::TreePop();
                    }
                    ImGui::Text("DT_CSPlayer m_iAccount: %d", p->money());
                    ImGui::Text("DT_BasePlayer m_iHealth: %d", p->health());
                    ImGui::Text("DT_BasePlayer m_iTeamNum: %d", p->team());
                    ImGui::Text("DT_CSPlayer m_fFlags: %d", p->flags());
                    ImGui::Text("DT_BaseEntity m_bSpotted: %d", p->spotted());
                    ImGui::Text("origin: %f %f %f", p->origin().x, p->origin().y, p->origin().y);
                    ImGui::Text("viewOffset: %f %f %f", p->viewOffset().x, p->viewOffset().y, p->viewOffset().y);
                    ImGui::TreePop();
                }
                ClientClass* clientClass = ent->clientClass();
                if (ImGui::TreeNode(std::to_string(i).c_str(), "%s (%d): %d", clientClass->m_pNetworkName, clientClass->m_ClassID, i)) {
                    ImGui::Text("DT_BaseEntity m_bSpotted: %d", ent->spotted());
                    ImGui::Text("origin: %f %f %f", ent->origin().x, ent->origin().y, ent->origin().y);
                    ImGui::TreePop();
                }
            }
        }
        ImGui::TreePop();
    }

    ImGui::End();
}