#include "../../includes.hpp"

bool Hooks::init() {
    Log::log("initialising hooks...");
    initSDL();
    Log::log("initialised hooks...");
    return true;
}

bool Hooks::unload() {
    Log::log("unloading hooks...");
    unloadSDL();
    Log::log("unloaded hooks!");
    return true;
}