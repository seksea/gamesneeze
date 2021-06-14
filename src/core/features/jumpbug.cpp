#include "features.hpp"
#include "../../includes.hpp"

float rad(float in) {
    return in * (M_PI / 180.f);
}

/*float distToGround(Player* p) {
    Trace ground_trace;
    Ray ray;
    Vector endpos = p->origin();
    endpos.z -= 8192;
    Vector mins = p->collideable().OBBMins();
    Vector maxs = p->collideable().OBBMaxs();
    TraceFilter filter;
    filter.pSkip = Globals::localPlayer;
    ray.Init(p->origin(), endpos, mins, maxs);
    Interfaces::trace->TraceRay(ray, MASK_PLAYERSOLID, &filter, &ground_trace);
    return std::fabs(p->origin().z - ground_trace.endpos.z);
}

void Features::JumpBug::createMove(CUserCmd* cmd) {
    // TODO: Use IInputSystem to check for spacebar
    if (CONFIGBOOL("Misc>Misc>Movement>Jump Bug")) { //&& Menu::CustomWidgets::isKeyDown(CONFIGINT("Misc>Misc>Movement>Jump Bug Key"))) {
        if (Globals::localPlayer && Globals::localPlayer->health() > 0) {
            if (!(Globals::localPlayer->flags() & FL_ONGROUND) ) { //&& cmd->buttons & IN_JUMP) {
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
}*/

/*for (int i = 0; i < 360; i += step) {
    vector start_origin = vector(radius * cos(rad(i)) + origin.x, radius * sin(rad(i)) + origin.y, origin.z);
    float distance = distance_to_ground(start_origin);

    if (distance > 4 && distance <= 8) {
        duck
    }
}*/

float distToGround(Vector origin) {
    Trace ground_trace;
    Ray ray;

    Vector endpos = origin;
    endpos.z -= 8192;

    Vector mins = Globals::localPlayer->collideable().OBBMins();
    Vector maxs = Globals::localPlayer->collideable().OBBMaxs();

    TraceFilter filter;
    filter.pSkip = Globals::localPlayer;

    ray.Init(origin, endpos, mins, maxs);
    Interfaces::trace->TraceRay(ray, MASK_PLAYERSOLID, &filter, &ground_trace);

    return std::fabs(origin.z - ground_trace.endpos.z);
}

void Features::JumpBug::createMove(CUserCmd* cmd) {
    if (CONFIGBOOL("Misc>Misc>Movement>Jump Bug")) { //&& Menu::CustomWidgets::isKeyDown(CONFIGINT("Misc>Misc>Movement>Jump Bug Key"))) {
        if (Globals::localPlayer && Globals::localPlayer->health() > 0) {
            if (!(Globals::localPlayer->flags() & FL_ONGROUND) ) { //&& cmd->buttons & IN_JUMP) {
                if (Globals::localPlayer->velocity().z < 0.f) { // Only check ground distance if we are falling
                    int step = 30;
                    for (int i = 0; i < 360; i += step) {
                        Vector origin = Globals::localPlayer->origin();
                        float radius = 10;
                        Vector start = Vector(radius * cos(rad(i)) + origin.x, radius * sin(rad(i)) + origin.y, origin.z);
                        float dist = distToGround(start);
                        if (dist <= 4.f) { // If we are 4u above the ground
                            cmd->buttons &= ~IN_DUCK;
                            cmd->buttons |= IN_JUMP;
                        } else if (dist > 4.f && dist <= 8.f) { // If we are between 4u and 8u from the ground
                            cmd->buttons |= IN_DUCK;
                            cmd->buttons &= ~IN_JUMP;
                        }
                    }
                }
            }
        }
    }
}
