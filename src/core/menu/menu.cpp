#include "../../includes.hpp"

#include "imgui/imgui.h"
#include "imgui/GL/gl3w.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"

void Menu::onPollEvent(SDL_Event* event, const int result) {
    if (result && ImGui_ImplSDL2_ProcessEvent(event) && Menu::open) {
        event->type = 0;
    }
}

void Menu::onSwapWindow(SDL_Window* window) {
    if (!initialised) {
        gl3wInit();
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplOpenGL3_Init("#version 100");
        initialised = true;
    }

    ImGui_ImplOpenGL3_NewFrame();

    ImGuiIO& io = ImGui::GetIO();
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    io.DisplaySize = ImVec2((float)w, (float)h);
    ImGui::NewFrame();

    ImGui::Begin("Test", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    ImGui::Text("pog");
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}