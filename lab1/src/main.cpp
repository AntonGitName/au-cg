// std
#include <memory>

// local
#include "WindowWrapper.h"
#include "BunnyRenderer.h"

int main() {

    auto window_wrapper = WindowWrapper(1024, 768, "Mandelbrot set");

    auto shader_wrapper = ShaderWrapper({{"./shaders/vertex.glsl", GL_VERTEX_SHADER},
                             {"./shaders/fragment.glsl", GL_FRAGMENT_SHADER}});
    auto pRenderer = std::make_shared<MandelbrotRenderer>(shader_wrapper);

    WindowWrapper::add_listener(window_wrapper.get_window(), pRenderer.get());

    window_wrapper.add_renderer(pRenderer.get());

    window_wrapper.loop();

    return 0;
}