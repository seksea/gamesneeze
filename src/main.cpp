#include "includes.hpp"

/* Thread to initialise everything in */
void MainThread() {
    std::cout << "Initialising...\n";

    std::cout << "Initialised!\n";
}

/* Called when injected */
void __attribute__((constructor)) Main() {
	std::thread mainThread(MainThread);
    
	mainThread.detach();
}

/* Called on uninject */
void __attribute__((destructor)) Unload() {
    std::cout << "Uninjecting...\n";

    std::cout << "Uninjected!\n\n";
}