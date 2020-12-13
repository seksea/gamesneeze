#include "../../includes.hpp"
#include "hooks.hpp"

bool Hooks::CreateMove::hook(void* thisptr, float flInputSampleTime, CUserCmd* cmd) {
    original(thisptr, flInputSampleTime, cmd);
    Log::log("Create Move!!");
    return false;
}