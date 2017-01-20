//
// Created by antonpp on 09.01.17.
//

#include "AbstractShaderRenderer.h"

AbstractShaderRenderer::AbstractShaderRenderer(std::shared_ptr<AbstractCamera> camera_ptr,
                                               std::shared_ptr<ShaderWrapper> shader_ptr)
    : camera_ptr(camera_ptr), shader_ptr(shader_ptr) {
    model = glm::mat4(1);
}

GLint AbstractShaderRenderer::get_uniform(const char *name) {
    return glGetUniformLocation(shader_ptr->get_program(), name);
}

void AbstractShaderRenderer::render(GLFWwindow *window) {

    setup_render(window);

    render_internal(window);
//    std::cout << "Render error: " << glGetError() << std::endl;
}

void AbstractShaderRenderer::setup_render(GLFWwindow *window) {
    glfwGetFramebufferSize(window, &width, &height);
    use_program();
    glUniformMatrix4fv(get_uniform("M"), 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(get_uniform("V"), 1, GL_FALSE, &camera_ptr->get_view()[0][0]);
    glUniformMatrix4fv(get_uniform("P"), 1, GL_FALSE, &camera_ptr->get_proj()[0][0]);
}

void AbstractShaderRenderer::use_program() {
    glUseProgram(shader_ptr->get_program());
}
