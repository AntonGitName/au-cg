//
// Created by antonpp on 08.01.17.
//

#ifndef AU_CG_OBJECTBUFFERSWRAPPER_H
#define AU_CG_OBJECTBUFFERSWRAPPER_H

// opengl
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/vec2.hpp>
#include <GL/glew.h>

// std
#include <vector>
#include <memory>

// local
#include "LoadedObject.h"

class ObjectBuffersWrapper {
public:
    ObjectBuffersWrapper(const ObjectBuffersWrapper&) = delete;
    ObjectBuffersWrapper(std::vector<glm::vec3> vertices);
    ObjectBuffersWrapper(LoadedObject obj, bool has_normals, bool has_uvs);
    ~ObjectBuffersWrapper();

    GLuint vao;
    size_t length;

    static std::shared_ptr<ObjectBuffersWrapper> load(std::string name, bool norm, bool uv);

private:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;

    GLuint v_vbo;
    GLuint uv_vbo;
    GLuint n_vbo;

    bool has_normals;
    bool has_uvs;
};


#endif //AU_CG_OBJECTBUFFERSWRAPPER_H
