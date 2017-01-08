//
// Created by Anton Mordberg on 08/01/2017.
//

#ifndef AU_CG_OBJ_UTIL_H
#define AU_CG_OBJ_UTIL_H

// opengl
#include <glm/detail/type_vec.hpp>

// std
#include <vector>

void load_obj_with_normals(const char * fname, std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals);

#endif //AU_CG_OBJ_UTIL_H
