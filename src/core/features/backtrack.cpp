#include "../../includes.hpp"
#include "features.hpp"
#include <cfloat>
#include <cstring>

void Features::Backtrack::store(CUserCmd *cmd) {
    if (CONFIGBOOL("Legit>Backtrack>Backtrack") && cmd->tick_count != 0 && Interfaces::engine->IsInGame() && Globals::localPlayer) {
        // Store
        BackTrackTick currentTick;
        for (int i = 1; i < Interfaces::globals->maxClients; i++) {
            Player* p = (Player*)Interfaces::entityList->GetClientEntity(i);
            if (p) {
                if (p->health() > 0 && !p->dormant() && p != Globals::localPlayer && p->isEnemy()) {
                    BacktrackPlayer player;
                    player.playerIndex = i;
                    player.playerFlags = p->flags();
                    player.playerVelocity = p->velocity().Length2D();
                    if (p->getAnythingBones(player.boneMatrix)) {
                        currentTick.players.insert(std::pair<int, BacktrackPlayer>(i, player));
                    }
                    player.playerHeadPos = Vector(player.boneMatrix[8][0][3], player.boneMatrix[8][1][3], player.boneMatrix[8][2][3]);
                }
                else {
                    if (currentTick.players.find(i) != currentTick.players.end()) {
                        currentTick.players.erase(i);
                    }
                }
            }
        }
        currentTick.tickCount = cmd->tick_count;
        backtrackTicks.insert(backtrackTicks.begin(), currentTick);

        // Delete ticks we cant backtrack
        while ((int)backtrackTicks.size() > CONFIGINT("Legit>Backtrack>Backtrack Ticks")) {
            backtrackTicks.pop_back();
        }
    }
}

void Features::Backtrack::createMove(CUserCmd* cmd) {
    if (CONFIGBOOL("Legit>Backtrack>Backtrack") && cmd->tick_count != 0 && Interfaces::engine->IsInGame() && Globals::localPlayer) {
        // Find how far we should backtrack in this tick
        QAngle viewAngles;
        Interfaces::engine->GetViewAngles(viewAngles);
        viewAngles += Globals::localPlayer->aimPunch() * 2;

        float closestDelta = FLT_MAX;
        int closestTick = cmd->tick_count;

        if (cmd->buttons & (1 << 0)) {
            for (BackTrackTick tick : backtrackTicks) {
                for (auto player : tick.players) {
                    Player* p = (Player*)Interfaces::entityList->GetClientEntity(player.second.playerIndex);
                    if (p) {
                        if (p->health() > 0 && !p->dormant()) {
                            Vector localPlayerEyePos = Globals::localPlayer->eyePos();

                            Vector targetEyePos = Vector(player.second.boneMatrix[8][0][3], player.second.boneMatrix[8][1][3], player.second.boneMatrix[8][2][3]); // 8 is headbone in bonematrix

                            QAngle angleToCurrentPlayer = calcAngle(localPlayerEyePos, targetEyePos);
                            angleToCurrentPlayer -= viewAngles;
                            if (angleToCurrentPlayer.y > 180.f) {
                                angleToCurrentPlayer.y -= 360.f;
                            }

                            if (angleToCurrentPlayer.Length() < closestDelta) {
                                closestDelta = angleToCurrentPlayer.Length();
                                closestTick = tick.tickCount;
                            }
                        }
                        else {
                            // If p is dormant or dead then erase player from the tick
                            tick.players.erase(player.first);
                        }
                    }
                    else {
                        // If p doesnt exist then erase player from the tick
                        tick.players.erase(player.first);
                    }
                }
            }
        }
        lastBacktrack = cmd->tick_count - closestTick; // To show how much you backtracked in hitlogs
        cmd->tick_count = closestTick;
    }
}
