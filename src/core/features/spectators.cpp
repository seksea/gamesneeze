#include "features.hpp"
#include "../../includes.hpp"

void Features::Spectators::draw() {
    if (CONFIGBOOL("Misc>Misc>Misc>Spectators")) {
		bool show_all = CONFIGBOOL("Misc>Misc>Misc>Show All Spectators");
		
        ImGui::Begin("Spectator List", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | (Menu::open ? 0 : ImGuiWindowFlags_NoMouseInputs));
        ImGui::Text(show_all ? "Spectators" : "Spectating You");
        ImGui::Separator();

		int local_idx = Interfaces::engine->GetLocalPlayer();
		Player* local = (Player*)Interfaces::entityList->GetClientEntity(local_idx);
			
		int local_target_idx = -1;		
		if(local && local->observerTarget())
			local_target_idx = (int)((uintptr_t)local->observerTarget() & 0xFFF);
        
        if (Interfaces::engine->IsInGame() && Globals::localPlayer) {
            for (int i = 0; i < Interfaces::globals->maxClients; i++) {
            	Player* p = (Player*)Interfaces::entityList->GetClientEntity(i);
				if (!p || p->dormant())
					continue;

				int target_idx = (int)((uintptr_t)p->observerTarget() & 0xFFF);
				if (target_idx <= 1 || target_idx >= Interfaces::globals->maxClients)
					continue;

				if(show_all) {
					Player* target = (Player*)Interfaces::entityList->GetClientEntity(target_idx);
					if (!target || target->dormant())
						continue;
							
					bool observer_local = i == local_idx;
					bool target_local = target_idx == local_idx;
					bool same_target = local_target_idx == target_idx;
	                player_info_t observer_info;
	                player_info_t target_info;
	                Interfaces::engine->GetPlayerInfo(i, &observer_info);
	                Interfaces::engine->GetPlayerInfo(target_idx, &target_info);
	                    
	                ImGui::TextColored(/*observer_local || */target_local || same_target ? ImColor(128, 0, 255) : ImColor(255, 255, 255),
	                    			   "%s -> %s",
	                    			   observer_local ? "you" : observer_info.name, 
	                    			   target_local ? "you" : target_info.name);
                } else {
                	if (target_idx != local_idx) 
						continue;

                    player_info_t observer_info;
                    Interfaces::engine->GetPlayerInfo(i, &observer_info);
                    ImGui::Text("%s", observer_info.name);
                }
            }
        }
        ImGui::End();
    }
}
