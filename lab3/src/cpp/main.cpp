// std
#include <memory>

// local
#include "WindowWrapper.h"
#include "CameraObject.h"
#include "ObjectRenderer.h"
#include "LightingSphere.h"
#include "ShadingObjectRenderer.h"
#include "ImageRenderer.h"

std::vector<std::shared_ptr<LightingSphere>> create_spheres(size_t n, std::shared_ptr<CameraObject> camera) {
    std::vector<std::shared_ptr<LightingSphere>> res;
    for (size_t i = 0; i < n; ++i) {
        res.push_back(std::make_shared<LightingSphere>(camera));
    }
    return res;
}

int main(int argc, char **argv) {
    srand(time(NULL));

    auto window_wrapper = WindowWrapper(1024, 768, "Phong shading");

    auto camera = std::make_shared<CameraObject>();

    auto spheres = create_spheres(8, camera);

    auto suzanne_renderer = std::make_shared<ShadingObjectRenderer>(camera);

    window_wrapper.add_renderer(suzanne_renderer);
    for (auto renderer: spheres) {
        window_wrapper.add_renderer(renderer);
        suzanne_renderer->add_light(renderer);
    }

    auto hypno_renderer = std::make_shared<ImageRenderer>(camera);
    window_wrapper.add_renderer(hypno_renderer);

    WindowWrapper::add_listener(window_wrapper.get_window(), camera);

    window_wrapper.loop();

    return 0;
}