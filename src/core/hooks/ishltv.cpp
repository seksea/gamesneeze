#include "../../includes.hpp"
#include "hooks.hpp"

bool Hooks::IsHLTV::hook(void* thisptr) {
    if (CONFIGBOOL("Misc>Misc>Misc>Force square radar")) {
        const auto returnAddress = (uintptr_t)__builtin_return_address(0);

        if (returnAddress == Offsets::radarIsHltvCheck) {
            return true;
        }
    }

    return original(thisptr);
}