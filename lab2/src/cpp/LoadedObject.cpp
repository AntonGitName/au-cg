//
// Created by antonpp on 08.01.17.
//

#include "LoadedObject.h"

namespace {
    void parse_face_vertex(const std::string& str, unsigned& v, unsigned& uv, unsigned& n) {
        std::vector<std::string> tokens;
        std::istringstream iss(str);
        std::copy(std::istream_iterator<std::string>(iss),
                  std::istream_iterator<std::string>(),
                  std::back_inserter(tokens));
        auto f = [](const std::string& s) { return s.empty() ? 0 : (unsigned int) (std::stoul(s) - 1);};
        v = f(tokens[0]);
        uv = f(tokens[1]);
        n = f(tokens[2]);
    }
}

LoadedObject::LoadedObject(std::string fname) {
    std::ifstream in(fname);
    if (!in) {
        throw std::runtime_error("Could not find obj file.");
    }

    std::string line;
    while (getline(in, line)) {
        if (line.substr(0, 2) == "v ") {
            std::istringstream s(line.substr(2));
            glm::vec3 v;
            s >> v.x >> v.y >> v.z;
            vertices.push_back(v);
        }
        if (line.substr(0, 2) == "vt ") {
            std::istringstream s(line.substr(3));
            glm::vec2 uv;
            s >> uv.x >> uv.y;
            uvs.push_back(uv);
        }
        if (line.substr(0, 2) == "vn ") {
            std::istringstream s(line.substr(3));
            glm::vec3 v;
            s >> v.x >> v.y >> v.z;
            normals.push_back(v);
        }
        if (line.substr(0, 1) == "f ") {
            std::istringstream s(line.substr(2));
            std::string v1, v2, v3;
            s >> v1 >> v2 >> v3;
            unsigned int v[3], uv[3], n[3];

            for (int i = 0; i < 3; ++i) {
                parse_face_vertex(v1, v[i], uv[i], n[i]);
                vertex_indices.push_back(v[i]);
                uv_indices.push_back(uv[i]);
                normal_indices.push_back(n[i]);
            }
        }
    }
}
