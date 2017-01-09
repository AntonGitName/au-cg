//
// Created by antonpp on 09.01.17.
//

#include "CameraCentered.h"

using namespace glm;

namespace {
    float dot(glm::vec3 v, glm::vec3 u) {
        return std::sqrt(v.x * u.x + v.y * u.y + v.z * u.z);
    }

    float length(glm::vec3 v) {
        return std::sqrt(dot(v, v));
    }
}

void CameraCentered::onKeyEvent(int key, int scancode, int action, int mods) {
    if (action == GLFW_RELEASE) {
        return;
    }

    switch (key) {
        case GLFW_KEY_RIGHT:
            phi -= 0.05;
            break;
        case GLFW_KEY_LEFT:
            phi += 0.05;
            break;
        case GLFW_KEY_UP:
            theta -= 0.05;
            break;
        case GLFW_KEY_DOWN:
            theta += 0.05;
            break;
        default:
            break;
    }
    if (theta > M_PI) {
        theta -= 2 * M_PI;
    }
    if (theta < - M_PI) {
        theta += 2 * M_PI;
    }
}

void CameraCentered::onMousePos(double x, double y) {

}

void CameraCentered::onMouseButton(int button, int action, int mods) {

}

void CameraCentered::onWindowSizeChanged(int width, int height) {

}

void CameraCentered::onMouseWheel(double xoffset, double yoffset) {
}


glm::mat4 CameraCentered::get_view() const {
    auto eye = vec3(r * sin(theta) * cos(phi), r * cos(theta), r * sin(theta) * sin(phi));
    auto up = vec3(0, theta > 0 ? 1 : -1, 0);
    return glm::lookAt(
            eye,
            glm::vec3(0, 0, 0),
            up
    );
}
