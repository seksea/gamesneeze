#include "features.hpp"
// Credit: AimTux/Fuzion

float m_flOldCurtime;
float m_flOldFrametime;

void Features::Prediction::start(CUserCmd* cmd) {
    inPrediction = true;
    if (Globals::localPlayer) {
        *Offsets::predictionSeed = rand() & 0x7FFFFFFF;

        m_flOldCurtime = Interfaces::globals->curtime;
        m_flOldFrametime = Interfaces::globals->frametime;

        Interfaces::globals->curtime = Globals::localPlayer->tickbase() * Interfaces::globals->interval_per_tick;
        Interfaces::globals->frametime = Interfaces::globals->interval_per_tick;

        Interfaces::movement->StartTrackPredictionErrors(Globals::localPlayer);

        Interfaces::moveHelper->SetHost(Globals::localPlayer);
        Interfaces::prediction->SetupMove(Globals::localPlayer, cmd, Interfaces::moveHelper, Offsets::moveData);
        Interfaces::movement->ProcessMovement(Globals::localPlayer, Offsets::moveData);
        Interfaces::prediction->FinishMove(Globals::localPlayer, cmd, Offsets::moveData);
    }
}

void Features::Prediction::end() {
    if (Globals::localPlayer) {
        Interfaces::movement->FinishTrackPredictionErrors(Globals::localPlayer);
        Interfaces::moveHelper->SetHost(0);

        *Offsets::predictionSeed = -1;

        Interfaces::globals->curtime = m_flOldCurtime;
        Interfaces::globals->frametime = m_flOldFrametime;
    }
    inPrediction = false;
}
