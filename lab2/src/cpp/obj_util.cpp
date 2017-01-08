//
// Created by Anton Mordberg on 08/01/2017.
//

#include <string>
#include <fstream>
#include <sstream>
#include <glm/detail/type_vec3.hpp>
#include "obj_util.h"

void load_obj_with_normals(const char * fname, std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals) {
    std::ifstream in(fname);
    if (!in) {
        throw std::runtime_error("Could not find obg file.");
    }

    std::string line;
    while (getline(in, line)) {
        if (line.substr(0, 2) == "v ") {
            std::istringstream s(line.substr(2));
            glm::vec3 v;
            s >> v.x >> v.y >> v.z;
            vertices.push_back(v);
        }
        if (line.substr(0, 2) == "vn ") {
            std::istringstream s(line.substr(3));
            glm::vec3 v;
            s >> v.x >> v.y >> v.z;
            normals.push_back(v);
        }
    }
}

