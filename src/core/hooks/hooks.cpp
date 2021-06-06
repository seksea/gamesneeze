#include "../../includes.hpp"
#include "hooks.hpp"
#include "vmt.hpp"
#include <chrono>
#include <thread>
#include <tuple>
#include <unistd.h>

static Hooks::Events::EventListener* eventListener = nullptr;

/* Create hooks */
bool Hooks::init() {
    Log::log(LOG, "Initialising hooks...");
    if (!SDL::initSDL()) {
        Log::log(ERR, " Failed to initialise SDL hooks!");
        return false;
    }

    Log::log(LOG, " Hooking CreateMove...");
    CreateMove::original = (CreateMove::func)VMT::hook(Interfaces::clientMode, (void*)CreateMove::hook, 25);

    Log::log(LOG, " Hooking Paint...");
    Paint::original = (Paint::func)VMT::hook(Interfaces::engineVgui, (void*)Paint::hook, 15);

    Log::log(LOG, " Hooking DrawModelExecute...");
    DrawModelExecute::original = (DrawModelExecute::func)VMT::hook(Interfaces::modelRender, (void*)DrawModelExecute::hook, 21);

    Log::log(LOG, " Hooking FrameStageNotify...");
    FrameStageNotify::original = (FrameStageNotify::func)VMT::hook(Interfaces::client, (void*)FrameStageNotify::hook, 37);

    Log::log(LOG, " Hooking EmitSound...");
    EmitSound::original = (EmitSound::func)VMT::hook(Interfaces::sound, (void*)EmitSound::hook, 6);

    Log::log(LOG, " Hooking IsHLTV...");
    IsHLTV::original = (IsHLTV::func)VMT::hook(Interfaces::engine, (void*)IsHLTV::hook, 93);

    Log::log(LOG, " Hooking ClientCmd...");
    ClientCmd::original = (ClientCmd::func)VMT::hook(Interfaces::engine, (void*)ClientCmd::hook, 7);

    Log::log(LOG, " Hooking OverrideView...");
    OverrideView::original = (OverrideView::func)VMT::hook(Interfaces::clientMode, (void*)OverrideView::hook, 19);

    Log::log(LOG, " Hooking GetViewmodelFOV... ");
    GetViewmodelFOV::original = (GetViewmodelFOV::func)VMT::hook(Interfaces::clientMode, (void*)GetViewmodelFOV::hook, 36);

    eventListener = new Events::EventListener;

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

    /* hook with original to do bigbrain unhooking */
    Log::log(LOG, " Unhooking CreateMove...");
    VMT::hook(Interfaces::clientMode, (void*)CreateMove::original, 25);

    Log::log(LOG, " Unhooking Paint...");
    VMT::hook(Interfaces::engineVgui, (void*)Paint::original, 15);

    Log::log(LOG, " Unhooking DME...");
    VMT::hook(Interfaces::modelRender, (void*)DrawModelExecute::original, 21);

    Log::log(LOG, " Unhooking FSN...");
    VMT::hook(Interfaces::client, (void*)FrameStageNotify::original, 37);

    Log::log(LOG, " Unhooking EmitSound...");
    VMT::hook(Interfaces::sound, (void*)EmitSound::original, 6);

    Log::log(LOG, " Unhooking IsHLTV...");
    VMT::hook(Interfaces::engine, (void*)IsHLTV::original, 93);

    Log::log(LOG, " Unhooking ClientCmd...");
    VMT::hook(Interfaces::engine, (void*)ClientCmd::original, 7);

    Log::log(LOG, " Unhooking OverrideView...");
    VMT::hook(Interfaces::clientMode, (void*)OverrideView::original, 19);

    Log::log(LOG, " Unhooking GetViewmodelFOV...");
    VMT::hook(Interfaces::clientMode, (void*)GetViewmodelFOV::original, 36);

    delete eventListener;

    Log::log(LOG, "Unloaded hooks!");
    return true;
}
