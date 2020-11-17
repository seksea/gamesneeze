namespace Menu {
    inline bool open = true;
    inline bool initialised = false;
    inline int tabSelected = 0;

    void drawMenu();
    void drawOverlay(ImDrawList* drawList);
    void onPollEvent(SDL_Event* event, const int result);
    void onSwapWindow(SDL_Window* window);
}