// std
#include <memory>

// local
#include "WindowWrapper.h"
#include "BunnyRenderer.h"
#include "CubeRenderer.h"
#include "CameraCentered.h"
#include "CameraObject.h"

int main(int argc, char **argv) {
    auto window_wrapper = WindowWrapper(1024, 768, "Bunny Reflection");

    auto bunny_camera = std::make_shared<CameraObject>();
    auto cube_camera = std::make_shared<CameraCentered>();

    auto cube_renderer = std::make_shared<CubeRenderer>(cube_camera);
    auto bunny_renderer = std::make_shared<BunnyRenderer>(bunny_camera);

    window_wrapper.add_renderer(cube_renderer.get());
    window_wrapper.add_renderer(bunny_renderer.get());

    WindowWrapper::add_listener(window_wrapper.get_window(), bunny_renderer.get());
    WindowWrapper::add_listener(window_wrapper.get_window(), bunny_camera.get());
    WindowWrapper::add_listener(window_wrapper.get_window(), cube_camera.get());

    window_wrapper.loop();

    return 0;
}