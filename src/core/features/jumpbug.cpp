#include "features.hpp"
#include "../../includes.hpp"

float distToGround(Player* p) {
    Trace ground_trace;
    Ray ray;
    Vector endpos = p->origin();
    Vector mins = p->collideable().OBBMins();
    Vector maxs = p->collideable().OBBMaxs();
    TraceFilterWorldAndPropsOnly filter;
    endpos.z -= 8192;
    ray.Init(p->origin(), endpos, mins, maxs);
    Interfaces::trace->TraceRay(ray, MASK_PLAYERSOLID, &filter, &ground_trace);
    return std::fabs(p->origin().z - ground_trace.endpos.z);
}

void Features::JumpBug::createMove(CUserCmd* cmd) {
    if (CONFIGBOOL("Misc>Misc>Movement>Jump Bug")) { //&& Menu::CustomWidgets::isKeyDown(CONFIGINT("Misc>Misc>Movement>Jump Bug Key"))) {
        if (Globals::localPlayer && Globals::localPlayer->health() > 0) {
            if (!(Globals::localPlayer->flags() & FL_ONGROUND) && cmd->buttons & IN_JUMP) {
                if (Globals::localPlayer->velocity().z < 0.f) { // Only check ground distance if we are falling
                    if (distToGround(Globals::localPlayer) <= 4.f) { // If we are 4u above the ground
                        cmd->buttons &= ~IN_DUCK;
                        cmd->buttons |= IN_JUMP;
                    } else if (distToGround(Globals::localPlayer) > 4.f && distToGround(Globals::localPlayer) <= 8.f) { // If we are between 4u and 20u from the ground
                        cmd->buttons |= IN_DUCK;
                        cmd->buttons &= ~IN_JUMP;
                    }
                }
            }
        }
    }
}
