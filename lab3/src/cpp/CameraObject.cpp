//
// Created by antonpp on 09.01.17.
//

#include "CameraObject.h"

using namespace glm;

void CameraObject::onWindowSizeChanged(int width, int height) {
    this->width = width;
    this->height = height;
    glViewport(0, 0, width, height);
}

void CameraObject::onKeyEvent(int key, int scancode, int action, int mods) {
    if (action == GLFW_RELEASE) {
        return;
    }

    switch (key) {
        case GLFW_KEY_W:
            cameraPos += camera_speed * cameraFront;
            break;
        case GLFW_KEY_S:
            cameraPos -= camera_speed * cameraFront;
            break;
        case GLFW_KEY_A:
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * camera_speed;
            break;
        case GLFW_KEY_D:
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * camera_speed;
            break;

        case GLFW_KEY_DOWN:
            rotations = rotate(rotations, +camera_speed, vec3{0, 1, 0});
            break;
        case GLFW_KEY_UP:
            rotations = rotate(rotations, -camera_speed, vec3{0, 1, 0});
            break;
        case GLFW_KEY_RIGHT:
            rotations = rotate(rotations, +camera_speed, vec3{0, 0, 1});
            break;
        case GLFW_KEY_LEFT:
            rotations = rotate(rotations, -camera_speed, vec3{0, 0, 1});
            break;
        default:
            break;
    }

}

void CameraObject::onMousePos(double xpos, double ypos) {
    vec2 current_mouse_position = {xpos, ypos};
    if (firstMouse) {
        last_mouse_position = current_mouse_position;
        firstMouse = false;
    }

    GLfloat xoffset = current_mouse_position.x - last_mouse_position.x;
    GLfloat yoffset = last_mouse_position.y - current_mouse_position.y;
    last_mouse_position = current_mouse_position;


    xoffset *= mouse_sensitivity;
    yoffset *= mouse_sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

void CameraObject::onMouseWheel(double xoffset, double yoffset) {
    if (fov >= 1.0f && fov <= 45.0f) {
        fov -= yoffset;
    }
    if (fov <= 1.0f) {
        fov = 1.0f;
    }
    if (fov >= 45.0f) {
        fov = 45.0f;
    }
}

CameraObject::CameraObject() {
    cameraUp = vec3{-0.40824829046, 0.81649658092, -0.40824829046};
    cameraPos = {0, 0, 10};
    cameraFront = {0, 0, -1};
}

glm::mat4 CameraObject::get_view() const {
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp) * rotations;
}

glm::mat4 CameraObject::get_proj() const {
    return glm::perspective(glm::radians(fov), (float) width / height, 0.01f, 2000.0f);
}
