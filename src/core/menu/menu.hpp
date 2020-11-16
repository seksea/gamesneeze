namespace Menu {
    inline bool open = true;
    inline bool initialised = false;

    void drawMenu();
    void onPollEvent(SDL_Event* event, const int result);
    void onSwapWindow(SDL_Window* window);
}