#include "../../includes.hpp"

/* Create hooks */
bool Hooks::init() {
    Log::log("Initialising hooks...");
    if (!initSDL()) {
        Log::err("Failed to initialise SDL hooks!");
        return false;
    }
    Log::log("Initialised hooks...");
    return true;
}

/* Unload hooks */
bool Hooks::unload() {
    Log::log("Unloading hooks...");

    if (!unloadSDL()) {
        Log::err("Failed to unload SDL hooks!");
        return false;
    }
    
    Log::log("Unloaded hooks!");
    return true;
}