// std
#include <memory>

// local
#include "WindowWrapper.h"
#include "BunnyRenderer.h"
#include "CubeRenderer.h"

int main(int argc, char **argv) {
    auto window_wrapper = WindowWrapper(1024, 768, "Bunny Reflection");

    auto cube_renderer = std::make_shared<CubeRenderer>();
    auto bunny_renderer = std::make_shared<BunnyRenderer>();

//    window_wrapper.add_renderer(bunny_renderer.get());
    window_wrapper.add_renderer(cube_renderer.get());

    window_wrapper.loop();

    return 0;
}