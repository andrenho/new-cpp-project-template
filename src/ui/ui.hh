#ifndef UI_UI_HH_
#define UI_UI_HH_

#include <chrono>

using hr = std::chrono::high_resolution_clock;
using Duration = decltype(hr::now() - hr::now());

class UI {
public:
    UI();
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
