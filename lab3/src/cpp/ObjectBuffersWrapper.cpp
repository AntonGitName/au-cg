//
// Created by antonpp on 08.01.17.
//

#include "ObjectBuffersWrapper.h"

ObjectBuffersWrapper::ObjectBuffersWrapper(LoadedObject obj, bool has_normals, bool has_uvs)
        : has_normals(has_normals), has_uvs(has_uvs) {

    length = obj.vertex_indices.size();
    for (auto i : obj.vertex_indices) {
        vertices.push_back(obj.vertices[i - 1]);
    }

    if (has_normals) {
        for (auto i : obj.normal_indices) {
            normals.push_back(obj.normals[i - 1]);
        }
    }

    if (has_uvs) {
        for (auto i : obj.uv_indices) {
                uvs.push_back(obj.uvs[i - 1]);
        }
    }

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &v_vbo);

    glBindVertexArray(vao);

    glGenBuffers(1, &v_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, v_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    if (has_normals) {
        glGenBuffers(1, &n_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, n_vbo);
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(1);
    }

    if (has_uvs) {
        glGenBuffers(1, &uv_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, uv_vbo);
        glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), uvs.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(2);
    }
}

ObjectBuffersWrapper::~ObjectBuffersWrapper() {
    if (has_normals) {
        glDeleteBuffers(1, &n_vbo);
    }

    if (has_uvs) {
        glDeleteBuffers(1, &uv_vbo);
    }

    glDeleteBuffers(1, &v_vbo);
    glDeleteVertexArrays(1, &vao);
}

ObjectBuffersWrapper::ObjectBuffersWrapper(std::vector<glm::vec3> vertices)
        : vertices(vertices), has_uvs(false), has_normals(false) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &v_vbo);

    glBindVertexArray(vao);

    glGenBuffers(1, &v_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, v_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
}
