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
        ImGui_ImplSDL2_InitForOpenGL(window, nullptr);
        initialised = true;
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window);

    ImGuiIO& io = ImGui::GetIO();
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    io.DisplaySize = ImVec2((float)w, (float)h);
    ImGui::NewFrame();

    if (Menu::open) {
        Menu::drawMenu();
    }


    if (ImGui::IsKeyPressed(SDL_SCANCODE_INSERT, false)) {
        Menu::open = !Menu::open;
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Menu::drawMenu() {
    ImGui::SetNextWindowSize(ImVec2{500, 400});
    ImGui::Begin("Gamesnooze lincuck edition", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    ImGui::Text("Gamesnooze lincuck edition");
    ImGui::Separator();
    ImGui::Text("pog");
    ImGui::End();
}