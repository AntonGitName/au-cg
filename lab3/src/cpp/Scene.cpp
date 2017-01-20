//
// Created by antonpp on 13.01.17.
//

#include "Scene.h"

void Scene::onKeyEvent(int key, int scancode, int action, int mods) {
    if (action == GLFW_RELEASE) {
        return;
    }

    switch (key) {
        case GLFW_KEY_PAGE_DOWN:
            WindowWrapper::update_speed(false);
            break;
        case GLFW_KEY_PAGE_UP:
            WindowWrapper::update_speed(true);
            break;

        case GLFW_KEY_MINUS:
            remove_light();
            break;
        case GLFW_KEY_EQUAL:
            add_light();
            break;

        default:
            break;
    }
}

void Scene::remove_light() {
    if (!lightsRenderers.empty()) {
        auto lr = lightsRenderers.back();
        lightsRenderers.pop_back();
        objectRenderer->remove_light(lr->light_info_ptr);
        imageRenderer->remove_light(lr->light_info_ptr);
    }
    update_renderers();
}

void Scene::add_light() {
    if (lightsRenderers.size() < MAX_LIGHTS) {
        auto lr = std::make_shared<LightingSphereRenderer>(camera_ptr);
        lightsRenderers.push_back(lr);
        objectRenderer->add_light(lr->light_info_ptr);
        imageRenderer->add_light(lr->light_info_ptr);
    }
    update_renderers();
}

Scene::Scene(std::shared_ptr<WindowWrapper> window) : window(window) {
    camera_ptr = std::make_shared<CameraObject>();
    imageRenderer = std::make_shared<PhongTextureRenderer>(camera_ptr);
    axisRenderer = std::make_shared<AxisRenderer>(camera_ptr);
    objectRenderer = std::make_shared<PhongObjectRenderer>(camera_ptr);
    for (int i = 0; i < 5; ++i) {
        add_light();
    }
    update_renderers();
    window->add_listener(camera_ptr);
}

void Scene::update_renderers() const {
    window->reset_renderers();
    window->add_renderer(imageRenderer);
    window->add_renderer(objectRenderer);
    window->add_renderer(axisRenderer);
    for (auto lr : lightsRenderers) {
        window->add_renderer(lr);
    }
}
