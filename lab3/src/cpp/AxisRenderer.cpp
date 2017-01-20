//
// Created by antonpp on 13.01.17.
//

#include "AxisRenderer.h"

using namespace glm;

std::shared_ptr<ShaderWrapper> AxisRenderer::g_shader = nullptr;

void AxisRenderer::render_internal(GLFWwindow *window) {
    glBindVertexArray (vao);
    glDrawArrays (GL_LINES, 0, (GLsizei) vertices.size());
}

AxisRenderer::AxisRenderer(std::shared_ptr<AbstractCamera> camera_ptr)
        : AbstractShaderRenderer(camera_ptr, get_g_shader()) {

    vertices = {
            vec3(+10, 0, 0),
            vec3(-10, 0, 0),

            vec3(0, +10, 0),
            vec3(0, -10, 0),

            vec3(0, 0, +10),
            vec3(0, 0, -10),
    };

    colors = {
            vec3(0.5, 0, 0),
            vec3(0.5, 0, 0),

            vec3(0, 0.5, 0),
            vec3(0, 0.5, 0),

            vec3(0, 0, 0.5),
            vec3(0, 0, 0.5),
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &v_vbo);

    glBindVertexArray(vao);

    glGenBuffers(1, &v_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, v_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &c_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, c_vbo);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);
}

AxisRenderer::~AxisRenderer() {
    glDeleteBuffers(1, &v_vbo);
    glDeleteBuffers(1, &c_vbo);
    glDeleteVertexArrays(1, &vao);
}


void AxisRenderer::init() {
    g_shader = std::make_shared<ShaderWrapper>(std::vector<std::pair<std::string, GLenum> >(
            {{"shaders/axis_vs.glsl", GL_VERTEX_SHADER},
             {"shaders/axis_fs.glsl", GL_FRAGMENT_SHADER}}));
}

std::shared_ptr<ShaderWrapper> AxisRenderer::get_g_shader() {
    if (!g_shader) {
        init();
    }
    return g_shader;
}