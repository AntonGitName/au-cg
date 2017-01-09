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

class CameraObject : public AbstractCamera, public AbstractWindowListener {
public:
    CameraObject();

    void onMouseWheel(double xoffset, double yoffset) override;

    void onWindowSizeChanged(int width, int height) override;

    void onMouseButton(int button, int action, int mods) override;

    void onMousePos(double x, double y) override;

    void onKeyEvent(int key, int scancode, int action, int mods) override;

    glm::mat4 get_view() const;
private:
    float theta = (float) M_PI_2;
    float phi = (float) M_PI_2;
    float r = 5;
};


#endif //AU_CG_CAMERA_H
