// std
#include <memory>

// local
#include "WindowWrapper.h"
#include "BunnyRenderer.h"

int main() {

    auto window_wrapper = WindowWrapper(1024, 768, "Bunny Reflection");

    auto bunny_renderer = std::make_shared<BunnyRenderer>();
    window_wrapper.add_renderer(bunny_renderer.get());

    window_wrapper.loop();

    return 0;
}