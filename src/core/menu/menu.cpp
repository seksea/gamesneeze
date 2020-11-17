#include "../../includes.hpp"

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

    Menu::drawOverlay(ImGui::GetBackgroundDrawList());
    if (Menu::open) {
        io.MouseDrawCursor = true;
        Menu::drawMenu();
    }
    else {
        io.MouseDrawCursor = false;
    }


    if (ImGui::IsKeyPressed(SDL_SCANCODE_INSERT, false)) {
        Menu::open = !Menu::open;
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Menu::drawMenu() {
    ImGui::SetNextWindowSize(ImVec2{500, 600});
    ImGui::Begin("linux-base", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    ImGui::Text("linux-base");
    ImGui::Separator();
    if (ImGui::BeginTabBar("mainTabs")) {
        if(ImGui::BeginTabItem("Legit")) {
            ImGui::Text("Legit");
            ImGui::EndTabItem();
        }
        if(ImGui::BeginTabItem("Rage")) {
            ImGui::Text("Rage");
            ImGui::EndTabItem();
        }
        if(ImGui::BeginTabItem("Visuals")) {
            ImGui::Text("Visuals");
            ImGui::EndTabItem();
        }
        if(ImGui::BeginTabItem("Misc")) {
            ImGui::Text("Misc");
            ImGui::EndTabItem();
        }
    ImGui::EndTabBar();
    }
    ImGui::End();
}