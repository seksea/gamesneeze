#include "features.hpp"
#include "../../includes.hpp"

void Features::VoteRevealer::event(IGameEvent* event) {
	if(!CONFIGBOOL("Misc>Misc>Misc>Vote Revealer"))
		return;

	if(!strstr(event->GetName(), "vote_cast"))
		return;

	int id = event->GetInt("entityid");
	Player* player = (Player*) Interfaces::entityList->GetClientEntity(id);
	if(!player)
		return;

	if(!CONFIGBOOL("Misc>Misc>Misc>Enemy Vote Revealer") && player->isEnemy())
		return;

	int vote = event->GetInt("vote_option"); // 0 = yes
	bool local = Globals::localPlayer && player == Globals::localPlayer;
	ImColor colors[2] = { ImColor(32, 255, 32), ImColor(255, 32, 32) };
	player_info_t playerInfo;
	Interfaces::engine->GetPlayerInfo(id, &playerInfo);
	Features::Notifications::addNotification(colors[vote], "[gs] voted %s:%s %s", vote ? "no" : "yes", player->isEnemy() ? " enemy" : "", local ? "you" : playerInfo.name);
}
