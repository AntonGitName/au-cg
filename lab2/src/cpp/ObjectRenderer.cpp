//
// Created by antonpp on 08.01.17.
//

#include "ObjectRenderer.h"

ObjectRenderer::ObjectRenderer(std::shared_ptr<AbstractCamera> camera_ptr, ObjectBuffersWrapper object, ShaderWrapper shader1)
    : camera_ptr(camera_ptr), object(std::move(object)), shader(std::move(shader1)) {
    model_id = glGetUniformLocation(shader.get_program(), "M");
    view_id = glGetUniformLocation(shader.get_program(), "V");

    model = glm::mat4(1);

    glUseProgram(shader.get_program());

}

void ObjectRenderer::render(GLFWwindow *window) {
    glfwGetFramebufferSize(window, &width, &height);

    glUseProgram(shader.get_program());
    glUniformMatrix4fv (model_id, 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv (view_id, 1, GL_FALSE, &camera_ptr->get_view()[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader.get_program(), "P"), 1, GL_FALSE, &camera_ptr->get_proj()[0][0]);
    glBindVertexArray (object.vao);
    glDrawArrays (GL_TRIANGLES, 0, (GLsizei) object.length);

//    std::cout << glGetError() << std::endl;
}
