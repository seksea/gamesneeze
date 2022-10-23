#include "core/menu/config.hpp"
#include "includes.hpp"
#include <unistd.h>

/* initialise everything in */
void MainThread() {
    /* if serverbrowser is not open then wait, (serverbrowser is last to be loaded) */
    while (!dlopen("./bin/linux64/serverbrowser_client.so", RTLD_NOLOAD | RTLD_NOW))
        usleep(500*1000);
    try {
        puts(" \n\
Powered by...\n\
   __ _  __ _ _ __ ___   ___ \e[32m ___ _ __   ___  ___ _______ \e[0m \n\
  / _` |/ _` | '_ ` _ \\ / _ \\\e[32m/ __| '_ \\ / _ \\/ _ \\_  / _ \\\e[0m \n\
 | (_| | (_| | | | | | |  __/\e[32m\\__ \\ | | |  __/  __// /  __/\e[0m \n\
  \\__, |\\__,_|_| |_| |_|\\___|\e[32m|___/_| |_|\\___|\\___/___\\___|\e[0m \n\
  |___/ \n\
===========================================================");
        Log::log(LOG, "Initialising...");

        Config::init();
        
        /* Initialise interfaces */
        if (!Interfaces::init()) {
            Log::log(ERR, "Failed to initialise interfaces!");
        }

        /* Initialise netvars/offsets */
        if (!Netvar::init()) {
            Log::log(ERR, "Failed to initialise netvars!");
        }

        /* Initialise hooks */
        if (!Hooks::init()) {
            Log::log(ERR, "Failed to initialise hooks!");
        }

        Features::Notifications::addNotification(ImColor(30, 255, 30), "[gs] Successfully injected!");
        Log::log(LOG, "Initialised!");
    }
    catch(const std::exception& e) {
        Log::log(ERR, e.what());
    }
}

/* Called on uninject, if you ld_preload with this, then it will call it as soon as you inject, so only have this if PRELOAD compile def is not set */
#ifndef PRELOAD
void __attribute__((destructor)) Unload() {
    Log::log(LOG, "Uninjecting...");

    /* Unload hooks */
    if (!Hooks::unload()) {
        Log::log(ERR, "Failed to unload hooks!");
    }

    /* Unload interfaces */
    if (!Interfaces::unload()) {
        Log::log(ERR, "Failed to unload interfaces!");
    }

    Log::log(LOG, "Uninjected!\n");
}
#endif

/* Called when injected */
int __attribute__((constructor)) Main() {
	std::thread mainThread(MainThread);
    
	mainThread.detach();
    return 0;
}
