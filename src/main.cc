#include "ui/ui.hh"

#include <chrono>
using hr = std::chrono::high_resolution_clock;

int main()
{
    UI ui(800, 600);

    auto last_frame = hr::now();
    while (ui.running()) {
        auto new_frame = hr::now();
        ui.update(new_frame - last_frame);
        ui.draw();
        last_frame = new_frame;
    }
}
