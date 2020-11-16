#include "includes.hpp"

/* Thread to initialise everything in */
void MainThread() {
    try {
        std::cout << R"(

Powered by...
  _     _                         _                    
 | |   (_)                       | |                   
 | |    _ _ __  _   ___  ________| |__   __ _ ___  ___ 
 | |   | | '_ \| | | \ \/ /______| '_ \ / _` / __|/ _ \
 | |___| | | | | |_| |>  <       | |_) | (_| \__ \  __/
 \_____/_|_| |_|\__,_/_/\_\      |_.__/ \__,_|___/\___|
========================================================
)";
        Log::log("initialising...");
        
        /* Initialise interfaces */
        if (!Interfaces::init()) {
            Log::err("Failed to initialise interfaces!");
        }

        /* Initialise hooks */
        if (!Hooks::init()) {
            Log::err("Failed to initialise hooks!");
        }

        Log::log("initialised!");
    }
    catch(const std::exception& e) {
        Log::err(e.what());
    }
}

/* Called on uninject */
void __attribute__((destructor)) Unload() {
    Log::log("uninjecting...");

    /* Unload hooks */
    if (!Hooks::unload()) {
        Log::err("Failed to unload hooks!");
    }

    /* Unload interfaces */
    if (!Interfaces::unload()) {
        Log::err("Failed to unload interfaces!");
    }

    Log::log("uninjected!\n");
}

/* Called when injected */
void __attribute__((constructor)) Main() {
	std::thread mainThread(MainThread);
    
	mainThread.detach();
}