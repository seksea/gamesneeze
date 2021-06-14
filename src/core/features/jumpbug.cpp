#include "features.hpp"
#include "../../includes.hpp"

float rad(float in) {
    return in * (M_PI / 180.f);
}

// TODO: Maybe try making the endpos a predicion to where we WILL land
float distToGround(Vector origin) {
    Trace trace;
    Ray ray;
    TraceFilter filter;
    filter.pSkip = Globals::localPlayer;

    Vector endpos = origin;
    endpos.z -= 8192;
    Vector mins = Globals::localPlayer->collideable().OBBMins();
    Vector maxs = Globals::localPlayer->collideable().OBBMaxs();

    ray.Init(origin, endpos, mins, maxs);
    Interfaces::trace->TraceRay(ray, MASK_PLAYERSOLID, &filter, &trace);

    return std::fabs(origin.z - trace.endpos.z);
}

void Features::JumpBug::createMove(CUserCmd* cmd) {
    if (CONFIGBOOL("Misc>Misc>Movement>Jump Bug") && Interfaces::inputSystem->IsButtonDown(KEY_SPACE)) {
        if (Globals::localPlayer && Globals::localPlayer->health() > 0) {
            if (Globals::localPlayer->velocity().z < 0.f) { // We are falling
                int step = 28; // 360 / step = number of traces we will do
                for (int i = 0; i < 360; i += step) {
                    Vector origin = Globals::localPlayer->origin();
                    float radius = 4; // How far out we will trace
                    Vector start = Vector(radius * cos(rad(i)) + origin.x, radius * sin(rad(i)) + origin.y, origin.z);
                    float dist = distToGround(start);
                    if (dist <= 4.f) { // Un-duck 4 units above the ground
                        cmd->buttons &= ~IN_DUCK;
                    } else if (dist > 4.f && dist <= 8.f) { // Duck when we are just above 4 units from the ground
                        cmd->buttons |= IN_DUCK;
                    }
                }
            }
        }
    }
}
