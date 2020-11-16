#include "includes.hpp"

/* Thread to initialise everything in */
void MainThread() {
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
    log::log("initialising...");
    
    /* Initialise interfaces */
    if (!interfaces::init()) {
        log::err("Failed to initialise interfaces!");
    }

    /* Initialise hooks */
    if (!hooks::init()) {
        log::err("Failed to initialise hooks!");
    }

    log::log("initialised!");
}

/* Called when injected */
void __attribute__((constructor)) Main() {
	std::thread mainThread(MainThread);
    
	mainThread.detach();
}

/* Called on uninject */
void __attribute__((destructor)) Unload() {
    log::log("uninjecting...");

    /* Unload hooks */
    if (!hooks::unload()) {
        log::err("Failed to unload hooks!");
    }

    /* Unload interfaces */
    if (!interfaces::unload()) {
        log::err("Failed to unload interfaces!");
    }

    log::log("uninjected!\n");
}