#include "../../includes.hpp"
#include "hooks.hpp"
#include "vmt.hpp"
#include <chrono>
#include <thread>
#include <tuple>
#include <unistd.h>

/* Create hooks */
bool Hooks::init() {
    Log::log(LOG, "Initialising hooks...");
    if (!SDL::initSDL()) {
        Log::log(ERR, " Failed to initialise SDL hooks!");
        return false;
    }

    Log::log(LOG, " Hooking CreateMove...");
    CreateMove::original = (CreateMove::func)VMT::hook(Interfaces::clientMode, (void*)CreateMove::hook, 25);

    Log::log(LOG, " Hooking PaintTraverse...");
    PaintTraverse::original = (PaintTraverse::func)VMT::hook(Interfaces::panel, (void*)PaintTraverse::hook, 42);

    Log::log(LOG, " Hooking Paint...");
    Paint::original = (Paint::func)VMT::hook(Interfaces::engineVgui, (void*)Paint::hook, 15);

    Log::log(LOG, " Hooking DME...");
    DrawModelExecute::original = (DrawModelExecute::func)VMT::hook(Interfaces::modelRender, (void*)DrawModelExecute::hook, 21);

    Log::log(LOG, "Initialised hooks!");
    return true;
}

/* Unload hooks */
bool Hooks::unload() {
    Log::log(LOG, "Unloading hooks...");

    if (!SDL::unloadSDL()) {
        Log::log(ERR, "Failed to unload SDL hooks!");
        return false;
    }

    /* hook with original to do bigrain unhooking */
    Log::log(LOG, " Unhooking CreateMove...");
    VMT::hook(Interfaces::clientMode, (void*)CreateMove::original, 25);

    Log::log(LOG, " Unhooking PaintTraverse...");
    VMT::hook(Interfaces::panel, (void*)PaintTraverse::original, 42);

    Log::log(LOG, " Unhooking Paint...");
    VMT::hook(Interfaces::engineVgui, (void*)Paint::original, 15);

    Log::log(LOG, " Unhooking DME...");
    VMT::hook(Interfaces::modelRender, (void*)DrawModelExecute::original, 21);

    Log::log(LOG, "Unloaded hooks!");
    return true;
}