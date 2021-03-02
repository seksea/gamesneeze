#include "../../includes.hpp"
#include "hooks.hpp"


void Hooks::OverrideView::hook(void* thisptr, ViewSetup* setup) {
    if (Interfaces::engine->IsInGame()) {
        if (Globals::localPlayer) {
            if (Globals::localPlayer->health() > 0) {
                if (!Globals::localPlayer->scoped()) {
                    setup->fov = CONFIGINT("Visuals>World>World>FOV");

                    // Third Person from Fuzion
                    QAngle viewAngles;
                    Interfaces::engine->GetViewAngles(viewAngles);
                    Trace tr;
                    Ray traceRay;
                    Vector eyePos = Globals::localPlayer->eyePos();

                    Vector camOff = Vector(cos(DEG2RAD(viewAngles.y)) * 100,
                                        sin(DEG2RAD(viewAngles.y)) * 100,
                                        sin(DEG2RAD(-viewAngles.x)) * 100);

                    traceRay.Init(eyePos, (eyePos - camOff));
                    TraceFilter traceFilter;
                    traceFilter.pSkip = Globals::localPlayer;
                    Interfaces::trace->TraceRay(traceRay, 0x1, &traceFilter, &tr);

                    if (CONFIGBOOL("Visuals>World>World>Third Person"))
                    Interfaces::input->m_vecCameraOffset = Vector(viewAngles.x, viewAngles.y, 100 * ((tr.fraction < 1.0f) ? tr.fraction : 1.0f) );
                    Interfaces::input->m_fCameraInThirdPerson = CONFIGBOOL("Visuals>World>World>Third Person");
                }
            }
        }
    }
    original(thisptr, setup);
}