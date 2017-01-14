//
// Created by antonpp on 09.01.17.
//

#ifndef AU_CG_CAMERA_H
#define AU_CG_CAMERA_H

// opengl
#include <glm/detail/type_mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

// local
#include "AbstractWindowListener.h"
#include "AbstractCamera.h"
#include "LightingSphereRenderer.h"

class CameraObject : public AbstractCamera, public AbstractWindowListener {
public:
    CameraObject();

    void onMouseWheel(double xoffset, double yoffset) override;
    void onWindowSizeChanged(int width, int height) override;
    void onKeyEvent(int key, int scancode, int action, int mods) override;
    void onMousePos(double x, double y);

    glm::mat4 get_view() const;
    glm::mat4 get_proj() const;
private:

    glm::mat4 rotations = glm::mat4(1);

    glm::vec3 cameraPos, cameraFront, cameraUp;

    float yaw    = -90.0f;
    float pitch  =  0.0f;
    float fov =  34.0f;

    bool firstMouse = true;

    int width = 1024;
    int height = 768;
    glm::vec2 last_mouse_position = {width / 2, height / 2};

    constexpr static float mouse_sensitivity = 0.20;
    float camera_speed = 0.1f;
};


#endif //AU_CG_CAMERA_H
