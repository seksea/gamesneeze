#include "features.hpp"

void Features::Nightmode::onTonemapController(TonemapController* tonemapController) {
    *tonemapController->useExposureMin_ptr() = CONFIGINT("Visuals>World>World>Nightmode") ? 1 : 0;
    *tonemapController->useExposureMax_ptr() = CONFIGINT("Visuals>World>World>Nightmode") ? 1 : 0;

                                                        // Divide by 201 so then it never hits 0, as when it hits 0 it will be ignored
    *tonemapController->exposureMin_ptr() = 0.5f - (CONFIGINT("Visuals>World>World>Nightmode") / 201.f);
    *tonemapController->exposureMax_ptr() = 0.5f - (CONFIGINT("Visuals>World>World>Nightmode") / 201.f);
}