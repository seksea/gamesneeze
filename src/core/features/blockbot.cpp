#include "../../includes.hpp"
#include "features.hpp"

// https://github.com/LWSS/Fuzion/blob/master/src/Hacks/autoblock.cpp
void Features::BlockBot::createMove(CUserCmd* cmd) {
	if (!CONFIGBOOL("Misc>Misc>Misc>Block Bot") || !Menu::CustomWidgets::isKeyDown(CONFIGINT("Misc>Misc>Misc>Block Bot Key")))
		return;


	if (!Globals::localPlayer || Globals::localPlayer->health() <= 0)
		return;

	float bestDist = 250.0f;
	int index = -1;

	for (int i = 0; i < Interfaces::globals->maxClients; i++) {
		Player* player = (Player*)Interfaces::entityList->GetClientEntity(i);
		
		if(!player || player->health() <= 0 || player->dormant() || player == Globals::localPlayer)
			continue;

		float dist = Globals::localPlayer->origin().DistTo(player->origin());

		if(dist < bestDist) {
			bestDist = dist;
			index = i;
		}		
	}

	// No player was found to block
	if (index == -1) 
		return;

	Player* target = (Player*)Interfaces::entityList->GetClientEntity(index);

	if (!target)
		return;

	QAngle angles = calcAngle(Globals::localPlayer->origin(), target->origin());
	angles.y -= Globals::localPlayer->viewAngles()->y;
	normalizeAngles(angles);
	
	if (angles.y < 0.0f)
		cmd->sidemove = 250.0f;
	else if (angles.y > 0)
		cmd->sidemove = -250.0f;		
}
