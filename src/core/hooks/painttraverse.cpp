#include "../../includes.hpp"
#include "hooks.hpp"

void Hooks::PaintTraverse::hook(void* thisptr, unsigned int vguiPanel, bool forceRepaint, bool allowForce) {
    original(thisptr, vguiPanel, forceRepaint, allowForce);
}