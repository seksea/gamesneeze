#include "../../includes.hpp"

bool interfaces::init() {
    log::log("initialising interfaces...");

    log::log("initialised interfaces...");
    return true;
}

bool interfaces::unload() {
    log::log("unloading interfaces...");

    log::log("unloaded interfaces!");
    return true;
}