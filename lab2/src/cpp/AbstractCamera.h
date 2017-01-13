//
// Created by antonpp on 09.01.17.
//

#ifndef AU_CG_ABSTRACTCAMERA_H
#define AU_CG_ABSTRACTCAMERA_H

// opengl
#include <glm/detail/type_mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

class AbstractCamera {
public:
    virtual glm::mat4 get_view() const = 0;
    glm::mat4 get_proj() { return proj;}

protected:
    glm::mat4 proj = glm::perspective(45.0f, (float) 4 / 3, 0.01f, 200.0f);;
};


#endif //AU_CG_ABSTRACTCAMERA_H
