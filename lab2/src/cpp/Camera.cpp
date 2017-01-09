//
// Created by antonpp on 09.01.17.
//

#include "Camera.h"

using namespace glm;

namespace {
    float dot(glm::vec3 v, glm::vec3 u) {
        return std::sqrt(v.x * u.x + v.y * u.y + v.z * u.z);
    }

    float length(glm::vec3 v) {
        return std::sqrt(dot(v, v));
    }
}

void Camera::onKeyEvent(int key, int scancode, int action, int mods) {
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

void Camera::onMousePos(double x, double y) {

}

void Camera::onMouseButton(int button, int action, int mods) {

}

void Camera::onWindowSizeChanged(int width, int height) {

}

void Camera::onMouseWheel(double xoffset, double yoffset) {
    float zoom_factor = (float) pow(1.1, std::abs(yoffset));
    auto prev_r = r;
    if (yoffset > 0) {
        r /= zoom_factor;
    } else {
        r *= zoom_factor;
    };
    if (r < 1. || r > 35) {
        r = prev_r;
    }
}

Camera::Camera() {}

glm::mat4 Camera::get_view() const {
    auto eye =  vec3(r * sin(theta) * cos(phi), r * cos(theta), r * sin(theta) * sin(phi));
    auto up = vec3(0, theta > 0 ? 1 : -1, 0);
    return glm::lookAt(
            eye,
            glm::vec3(0, 0, 0),
            up
    );
}
