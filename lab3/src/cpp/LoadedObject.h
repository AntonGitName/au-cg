//
// Created by antonpp on 08.01.17.
//

#ifndef AU_CG_LOADEDOBJECT_H
#define AU_CG_LOADEDOBJECT_H

// opengl
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/vec2.hpp>
#include <GL/glew.h>

// std
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>

struct LoadedObject {
    LoadedObject(std::string fname);

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;
    std::vector<unsigned> vertex_indices;
    std::vector<unsigned> uv_indices;
    std::vector<unsigned> normal_indices;
};


#endif //AU_CG_LOADEDOBJECT_H
