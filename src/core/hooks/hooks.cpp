#include "../../includes.hpp"

/* Create hooks */
bool Hooks::init() {
    Log::log("initialising hooks...");
    if (!initSDL()) {
        Log::err("Failed to initialise SDL hooks!");
        return false;
    }
    Log::log("initialised hooks...");
    return true;
}

/* Unload hooks */
bool Hooks::unload() {
    Log::log("unloading hooks...");

    if (!unloadSDL()) {
        Log::err("Failed to unload SDL hooks!");
        return false;
    }
    
    Log::log("unloaded hooks!");
    return true;
}