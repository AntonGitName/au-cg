//
// Created by antonpp on 06.01.17.
//

#include "BunnyRenderer.h"

BunnyRenderer::BunnyRenderer(std::shared_ptr<AbstractCamera> camera_ptr)
        : ObjectRenderer(camera_ptr,
                         ObjectBuffersWrapper(LoadedObject("obj/bunny_with_normals.obj"), true, false),
                         ShaderWrapper({{"shaders/bunny_vs.glsl", GL_VERTEX_SHADER},
                                        {"shaders/bunny_fs.glsl", GL_FRAGMENT_SHADER}})) {
    model = glm::scale(model, glm::vec3(10, 10, 10));
}

void BunnyRenderer::onKeyEvent(int key, int scancode, int action, int mods) {
    if (action == GLFW_RELEASE) {
        return;
    }

    switch (key) {
        case GLFW_KEY_W:
            model = glm::rotate(model, -0.05f, glm::vec3(1, 0, 0));
            break;
        case GLFW_KEY_S:
            model = glm::rotate(model, 0.05f, glm::vec3(1, 0, 0));
            break;
        case GLFW_KEY_A:
            model = glm::rotate(model, -0.05f, glm::vec3(0, 1, 0));
            break;
        case GLFW_KEY_D:
            model = glm::rotate(model, 0.05f, glm::vec3(0, 1, 0));
            break;
        deafault:
            break;
    }

}
