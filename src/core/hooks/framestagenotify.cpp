#include "../../includes.hpp"
#include "hooks.hpp"

void Hooks::FrameStageNotify::hook(void* thisptr, FrameStage frame) {
    Globals::localPlayer = (Player*)Interfaces::entityList->GetClientEntity(Interfaces::engine->GetLocalPlayer());
    Features::ClantagChanger::frameStageNotify(frame);
    Features::SkyboxChanger::frameStageNotify(frame);
    Features::RecoilCrosshair::frameStageNotify(frame);
    Features::SkinChanger::frameStageNotify(frame);
    Features::NoFlash::frameStageNotify(frame);

    if (frame == FRAME_RENDER_START) {
        cachePlayers();
        if (Globals::localPlayer) {
            if (Globals::localPlayer->health() > 0) {
                if (Interfaces::input->m_fCameraInThirdPerson) {
                    QAngle viewAngles;
                    Interfaces::engine->GetViewAngles(viewAngles);
                    Globals::localPlayer->viewAngles()->y = CONFIGBOOL("Rage>Enabled") ? Features::AntiAim::fakeYaw : viewAngles.y;
                    Globals::localPlayer->viewAngles()->x = CONFIGBOOL("Rage>Enabled") ? CONFIGINT("Rage>AntiAim>Pitch") : viewAngles.x;
                }
            }
        }
    }

    if (frame == FRAME_NET_UPDATE_POSTDATAUPDATE_START) {
        if (CONFIGBOOL("Rage>RageBot>Default>Resolver")) {
            for (int i = 1; i < Interfaces::globals->maxClients; i++) {
                Player* p = (Player*)Interfaces::entityList->GetClientEntity(i);
                if (p && p != Globals::localPlayer) {
                    if (p->health() > 0 && !p->dormant() && p->team() != Globals::localPlayer->team()) {
                        p->eyeAngles_ptr()->y = p->lbyTarget() + (rand() % 100) - 50; // p resolve
                    }
                }
            }
        }
    }

    original(thisptr, frame);
}