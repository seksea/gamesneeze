#include "../../includes.hpp"
#include "hooks.hpp"


void Hooks::Paint::hook(void* thisptr, PaintMode_t mode) {
    original(thisptr, mode);
    if (mode & PAINT_UIPANELS) {
        Globals::worldToScreenMatrix = Interfaces::engine->WorldToScreenMatrix();
    }
}