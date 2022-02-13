#include "features.hpp"
#include "../../includes.hpp"

struct PlayerDamageInfo {
	int player_idx = -1;
	int damage = -1;
	int kills = -1;	
};

#define PLAYERDAMAGE_SIZE 64
PlayerDamageInfo playerDamage[PLAYERDAMAGE_SIZE];
int top_idx = 0;

void addToList(int player_idx, int damage, int kills) {	
	int idx = -1;
	for(int i = 0; i < PLAYERDAMAGE_SIZE; i++) {
		if(playerDamage[i].player_idx == player_idx)
			idx = i;
	}

	if(idx == -1) {
		playerDamage[top_idx] = (struct PlayerDamageInfo) {
			.player_idx = player_idx,
			.damage = damage,
			.kills = kills
		};
		top_idx++;
		if(top_idx >= PLAYERDAMAGE_SIZE) {
			Features::Notifications::addNotification(ImColor(255, 0, 0), "[gs] WARNING: TOO MANY TEAMDAMAGE LIST ENTRIES. PLEASE CLEAR!");
			top_idx = PLAYERDAMAGE_SIZE - 1;
		}
	} else {
		playerDamage[idx].damage += damage;
		playerDamage[idx].kills += kills;
	}
}

void Features::DamageList::event(IGameEvent* event) {
	if(!strstr(event->GetName(), "player_hurt") && !strstr(event->GetName(), "player_death"))
		return;

	int attacker_idx = Interfaces::engine->GetPlayerForUserID(event->GetInt("attacker"));
	int victim_idx = Interfaces::engine->GetPlayerForUserID(event->GetInt("userid"));
	Player* attacker = (Player*)Interfaces::entityList->GetClientEntity(attacker_idx);
    Player* victim = (Player*)Interfaces::entityList->GetClientEntity(victim_idx);

	if(!attacker || !victim) 
    	return;

	if(attacker == victim)
    	return;

	if(attacker->team() != Globals::localPlayer->team() || victim->team() != Globals::localPlayer->team())
    	return;


	int damage = 0;
	int kills = 0;
	if(strstr(event->GetName(), "player_death")) {
		kills = 1;
		damage = victim->health();
	} else {
		if(event->GetInt("dmg_health") < victim->health())
			damage = event->GetInt("dmg_health");
	}

	addToList(attacker_idx, damage, kills);
}	

void Features::DamageList::draw() {
	if (!CONFIGBOOL("Misc>Misc>Misc>Damage List") || !(CONFIGBOOL("Misc>Misc>Misc>Damage List Only When Menu Open") ? Menu::open : true))
		return; 

	ImGui::SetNextWindowContentSize(ImVec2(250, 0.0f));
	ImGui::Begin("Damage List", nullptr, ImGuiWindowFlags_NoTitleBar | 
										 ImGuiWindowFlags_NoCollapse | 
										 ImGuiWindowFlags_AlwaysAutoResize |
										 (Menu::open ? 0 : ImGuiWindowFlags_NoMouseInputs));
	ImGui::Text("Damage List");
	ImGui::Separator();

	ImGui::Columns(3, NULL);
	ImGui::Text("Name");
	ImGui::NextColumn();
	ImGui::Text("Kills");
	ImGui::NextColumn();
	ImGui::Text("Damage");
	ImGui::NextColumn();

	for(int i = 0; i < top_idx; i++) {
		PlayerDamageInfo* damageInfo = &playerDamage[i];
		Player* player = (Player*)Interfaces::entityList->GetClientEntity(damageInfo->player_idx);
		if(!player)
			continue;

		if(player->isEnemy())
			continue;

		ImGui::Separator();

		player_info_t info;
		Interfaces::engine->GetPlayerInfo(damageInfo->player_idx, &info);

		ImColor killsColor = ImColor(0, 255, 0);
		if(damageInfo->kills == 1)
			killsColor = ImColor(255, 128, 0);
		else if(damageInfo->kills > 1)
			killsColor = ImColor(255, 0, 0);
		
		ImColor damageColor = ImColor(0, 255, 0);
		ImGui::ColorConvertHSVtoRGB(((300.f - (float)damageInfo->damage) / 300.f * 80.f) / 255.f, 1.f, 1.f, damageColor.Value.x, damageColor.Value.y, damageColor.Value.z);

		ImGui::Text("%s", info.name);
		ImGui::NextColumn();
		ImGui::TextColored(killsColor, "%d", damageInfo->kills);
		ImGui::NextColumn();
		ImGui::TextColored(damageColor, "%d", damageInfo->damage);
		ImGui::NextColumn();
	}

	ImGui::End();
}

void Features::DamageList::clearList() {
	top_idx = 0;
}
