// std
#include <memory>

// local
#include "WindowWrapper.h"
#include "CameraObject.h"
#include "ObjectRenderer.h"

int main(int argc, char **argv) {
    auto window_wrapper = WindowWrapper(1024, 768, "Phong shading");

    auto camera = std::make_shared<CameraObject>();

    auto obw = ObjectBuffersWrapper(LoadedObject("obj/sphere.obj"), true, false);
    auto shader = ShaderWrapper({{"shaders/point_light_vs.glsl", GL_VERTEX_SHADER},
                           {"shaders/point_light_fs.glsl", GL_FRAGMENT_SHADER}});
    auto renderer = std::make_shared<ObjectRenderer>(camera, std::move(obw), std::move(shader));

    window_wrapper.add_renderer(renderer.get());

    WindowWrapper::add_listener(window_wrapper.get_window(), camera.get());

    window_wrapper.loop();

    return 0;
}