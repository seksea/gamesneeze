#include "../../includes.hpp"

template <typename T>
static constexpr auto relativeToAbsolute(std::uintptr_t address) noexcept
{
    return (T)(address + 4 + *reinterpret_cast<std::int32_t*>(address));
}

void Hooks::SwapWindow(SDL_Window* window) {
    SDL_Surface* screenSurface = SDL_GetWindowSurface(window);

    SDL_Rect rect{0, 0, 100, 100};
    SDL_FillRect(screenSurface, &rect, SDL_MapRGB(screenSurface->format, 0xff, 0xff, 0xff));
    
    /*static const auto _ = ImGui_ImplSDL2_InitForOpenGL(window, nullptr);

    if (ESP::loadScheduledFonts()) {
        ImGui_ImplOpenGL3_DestroyDeviceObjects();
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window);

    ImGui::NewFrame();

    if (const auto& displaySize = ImGui::GetIO().DisplaySize; displaySize.x > 0.0f && displaySize.y > 0.0f) {
        ESP::render();
        Misc::draw(ImGui::GetBackgroundDrawList());
        gui->render();
    }

    if (ImGui::IsKeyPressed(SDL_SCANCODE_INSERT, false)) {
        gui->open = !gui->open;
        if (!gui->open)
            interfaces->inputSystem->resetInputState();
    }
    ImGui::GetIO().MouseDrawCursor = gui->open;

    ImGui::EndFrame();
    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());*/
    swapWindow(window);
}

void Hooks::initSDL() {
    Log::log("initialising OpenGL Hooks...");
    const auto libSDL = dlopen("libSDL2-2.0.so.0", RTLD_LAZY | RTLD_NOLOAD);
    swapWindowAddr = relativeToAbsolute<uintptr_t>(uintptr_t(dlsym(libSDL, "SDL_GL_SwapWindow")) + 3);
    swapWindow = *reinterpret_cast<decltype(swapWindow)*>(swapWindowAddr);
    Log::log(std::string("swapwindow >> ") + std::to_string(swapWindowAddr));
}

void Hooks::unloadSDL() {
    Log::log("unloading OpenGL Hooks...");
    *reinterpret_cast<decltype(swapWindow)*>(swapWindowAddr) = swapWindow;
}