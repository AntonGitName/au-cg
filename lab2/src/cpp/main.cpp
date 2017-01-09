// std
#include <memory>

// local
#include "WindowWrapper.h"
#include "BunnyRenderer.h"
#include "CubeRenderer.h"

int main(int argc, char **argv) {
    auto window_wrapper = WindowWrapper(1024, 768, "Bunny Reflection");

    auto camera_ptr = std::make_shared<Camera>();
    auto cube_renderer = std::make_shared<CubeRenderer>(camera_ptr);
    auto bunny_renderer = std::make_shared<BunnyRenderer>(camera_ptr);

    window_wrapper.add_renderer(cube_renderer.get());
    window_wrapper.add_renderer(bunny_renderer.get());

    WindowWrapper::add_listener(window_wrapper.get_window(), camera_ptr.get());

    window_wrapper.loop();

    return 0;
}