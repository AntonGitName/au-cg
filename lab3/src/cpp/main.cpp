// std
#include <memory>

// local
#include "WindowWrapper.h"
#include "CameraObject.h"
#include "ShadingObjectRenderer.h"
#include "Scene.h"

int main(int argc, char **argv) {
    srand(time(NULL));

    auto window_wrapper = std::make_shared<WindowWrapper>(1024, 768, "Phong shading");

    auto scene = std::make_shared<Scene>(window_wrapper);

    window_wrapper->add_listener(scene);

    window_wrapper->loop();

    return 0;
}