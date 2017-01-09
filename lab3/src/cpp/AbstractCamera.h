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
    virtual glm::mat4 get_proj() const = 0;
};


#endif //AU_CG_ABSTRACTCAMERA_H
