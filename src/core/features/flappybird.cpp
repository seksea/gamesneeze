#include "features.hpp"
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_scancode.h>
#include <vector>

int score;
ImVec2 cursorPos;
float deltaTime;
bool alive = true;
float birdHeight;

class Bird {
public:
    void draw(ImDrawList* drawList) {
        drawList->AddRectFilled(ImVec2{cursorPos.x+60, cursorPos.y+(400-height)}, ImVec2{cursorPos.x+70, cursorPos.y+(400-height)+10}, ImColor(255, 255, 255, 255));
        if (alive) {
            height += velocity*deltaTime; // add velocity
            birdHeight = height;
            velocity -= 250.f*deltaTime; // gravity
            if (height < 50) {
                alive = false;
            }
        }
        else {
            drawList->AddText(ImVec2{ImVec2{cursorPos.x+10, cursorPos.y+10}}, ImColor(255, 255, 255, 255), "You died, press up arrow to respawn");
        }
    }

    void handleInput() {
        if (alive) {
            if (ImGui::IsKeyPressed(SDL_SCANCODE_UP, false)) {
                velocity = 140.f;
            }
        }
        else {
            if (ImGui::IsKeyPressed(SDL_SCANCODE_UP, false)) {
                alive = true;
                score = 0;
                velocity = 0;
                height = 300;
            }
        }
    }

    float velocity = 0;
    float height = 300;
};

class Pipe {
public:
    Pipe(float startX) {
        x = startX;
        xOriginal = startX;
        gapTop = (rand() % 200) + 130;
        gapBottom = gapTop - 65;
    }

    void draw(ImDrawList* drawList) {
        drawList->AddRectFilled(ImVec2{cursorPos.x+x, cursorPos.y}, ImVec2{cursorPos.x+x+40, cursorPos.y+(400-gapTop)}, ImColor(0, 65, 0, 255));
        drawList->AddRectFilled(ImVec2{cursorPos.x+x, cursorPos.y+400}, ImVec2{cursorPos.x+x+40, cursorPos.y+(400-gapBottom)}, ImColor(0, 65, 0, 255));
        if (alive) {
            x -= 90.f*deltaTime;
            if (x < -200) {
                x = 400;
                gapTop = (rand() % 200) + 130;
                gapBottom = gapTop - 65;
                hasBirdPassed = false;
            }
            if ((x < 70) && (x > 20)) {
                if ((birdHeight > gapTop) || (birdHeight < gapBottom)) {
                    alive = false;
                }
                if (!hasBirdPassed) {
                    score++;
                    hasBirdPassed = true;
                }
            }
        }
        else {
            x = xOriginal;
            gapTop = (rand() % 200) + 130;
            gapBottom = gapTop - 65;
            hasBirdPassed = false;
        }
    }
    bool hasBirdPassed = false;
    float gapTop = 300, gapBottom = 235;
    float x;
    float xOriginal;
};

void Features::FlappyBird::draw() {
    if (CONFIGBOOL("Misc>Misc>Misc>Flappy Birb")) {
        ImGui::Begin("Flappy Birb", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | (Menu::open ? 0 : ImGuiWindowFlags_NoMouseInputs));
        ImGui::Text("Flappy Birb (Score %i)", score);
        ImGui::Separator();

        ImDrawList* drawList = ImGui::GetWindowDrawList();
        deltaTime = ImGui::GetIO().DeltaTime;
        cursorPos = ImGui::GetCursorScreenPos();

        drawList->AddRectFilled(ImVec2{cursorPos.x, cursorPos.y}, ImVec2{cursorPos.x+400, cursorPos.y+400}, ImColor(0, 0, 0, 255));
        drawList->AddRectFilled(ImVec2{cursorPos.x, cursorPos.y+360}, ImVec2{cursorPos.x+400, cursorPos.y+400}, ImColor(0, 80, 0, 255));

        static Bird bird;
        bird.handleInput();
        bird.draw(drawList);

        static Pipe pipe(400);
        pipe.draw(drawList);

        static Pipe pipe2(550);
        pipe2.draw(drawList);

        static Pipe pipe3(700);
        pipe3.draw(drawList);

        ImGui::End();
    }
}