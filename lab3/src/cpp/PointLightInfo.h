//
// Created by antonpp on 20.01.17.
//

#ifndef AU_CG_POINTLIGHTINFO_H
#define AU_CG_POINTLIGHTINFO_H


#include <GL/gl.h>
#include <glm/vec3.hpp>

struct PointLightInfo {
    glm::vec3 specular_color;
    glm::vec3 diffuse_color;
    glm::vec3 position;
    glm::vec3 diffuse_coef;
    glm::vec3 specular_coef;
    GLfloat specular_exponent;
};


#endif //AU_CG_POINTLIGHTINFO_H
