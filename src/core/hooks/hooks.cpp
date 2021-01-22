#include "../../includes.hpp"
#include "hooks.hpp"
#include "vmt.hpp"
#include <chrono>
#include <thread>
#include <tuple>
#include <unistd.h>

/* Create hooks */
bool Hooks::init() {
    Log::log("Initialising hooks...");
    if (!SDL::initSDL()) {
        Log::err("Failed to initialise SDL hooks!");
        return false;
    }

    Log::log(" Hooking CreateMove...");
    CreateMove::original = (CreateMove::func)VMT::hook(Interfaces::clientMode, (void*)CreateMove::hook, 25);

    Log::log(" Hooking PaintTraverse...");
    PaintTraverse::original = (PaintTraverse::func)VMT::hook(Interfaces::panel, (void*)PaintTraverse::hook, 42);

    Log::log(" Hooking Paint...");
    Paint::original = (Paint::func)VMT::hook(Interfaces::engineVgui, (void*)Paint::hook, 15);

    Log::log(" Hooking DME...");
    DrawModelExecute::original = (DrawModelExecute::func)VMT::hook(Interfaces::modelRender, (void*)DrawModelExecute::hook, 21);

    Log::log("Initialised hooks!");
    return true;
}

/* Unload hooks */
bool Hooks::unload() {
    Log::log("Unloading hooks...");

    if (!SDL::unloadSDL()) {
        Log::err("Failed to unload SDL hooks!");
        return false;
    }

    /* hook with original to do bigrain unhooking */
    Log::log(" Unhooking CreateMove...");
    VMT::hook(Interfaces::clientMode, (void*)CreateMove::original, 25);

    Log::log(" Unhooking PaintTraverse...");
    VMT::hook(Interfaces::panel, (void*)PaintTraverse::original, 42);

    Log::log(" Unhooking Paint...");
    VMT::hook(Interfaces::engineVgui, (void*)Paint::original, 15);

    Log::log(" Unhooking DME...");
    VMT::hook(Interfaces::modelRender, (void*)DrawModelExecute::original, 21);

    Log::log("Unloaded hooks!");
    return true;
}