#ifndef UI_UI_HH_
#define UI_UI_HH_

#include <chrono>

using Duration = decltype(std::chrono::high_resolution_clock::now() - std::chrono::high_resolution_clock::now());

class UI {
public:
    UI(int w, int h);
    ~UI();
    UI (const UI&) = delete;
    UI& operator=(const UI&) = delete;

    void update([[maybe_unused]] Duration timestep);
    void draw();

    [[nodiscard]] bool running() const { return running_; }

private:
    bool running_ = true;

    struct SDL_Window*   window_;
    struct SDL_Renderer* ren_;
    struct SDL_Texture*  texture_;
};

#endif
