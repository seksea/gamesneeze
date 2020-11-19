#include "includes.hpp"

/* Thread to initialise everything in */
void MainThread() {
    try {
        std::cout << " \n\
Powered by...\n\
   __ _  __ _ _ __ ___   ___ \e[32m ___ _ __   ___  ___ _______ \e[0m \n\
  / _` |/ _` | '_ ` _ \\ / _ \\\e[32m/ __| '_ \\ / _ \\/ _ \\_  / _ \\\e[0m \n\
 | (_| | (_| | | | | | |  __/\e[32m\\__ \\ | | |  __/  __// /  __/\e[0m \n\
  \\__, |\\__,_|_| |_| |_|\\___|\e[32m|___/_| |_|\\___|\\___/___\\___|\e[0m \n\
  |___/ \n\
===========================================================\n";
        Log::log("Initialising...");
        
        /* Initialise interfaces */
        if (!Interfaces::init()) {
            Log::err("Failed to initialise interfaces!");
        }

        /* Initialise hooks */
        if (!Hooks::init()) {
            Log::err("Failed to initialise hooks!");
        }

        Log::log("Initialised!");
    }
    catch(const std::exception& e) {
        Log::err(e.what());
    }
}

/* Called on uninject */
void __attribute__((destructor)) Unload() {
    Log::log("Uninjecting...");

    /* Unload hooks */
    if (!Hooks::unload()) {
        Log::err("Failed to unload hooks!");
    }

    /* Unload interfaces */
    if (!Interfaces::unload()) {
        Log::err("Failed to unload interfaces!");
    }

    Log::log("Uninjected!\n");
}

/* Called when injected */
void __attribute__((constructor)) Main() {
	std::thread mainThread(MainThread);
    
	mainThread.detach();
}