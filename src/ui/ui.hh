#ifndef UI_UI_HH_
#define UI_UI_HH_

#include <chrono>

class UI {
public:
    void initialize();

    using Duration = decltype(std::chrono::high_resolution_clock::now() - std::chrono::high_resolution_clock::now());
    void update([[maybe_unused]] Duration timestep);
    void draw();

    [[nodiscard]] bool running() const { return running_; }

private:
    bool running_ = true;
};

#endif
