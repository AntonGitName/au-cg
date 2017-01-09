//
// Created by antonpp on 08.01.17.
//

#include "ObjectRenderer.h"

ObjectRenderer::ObjectRenderer(std::shared_ptr<AbstractCamera> camera_ptr,
                               std::shared_ptr<ShaderWrapper> shader_ptr,
                               std::shared_ptr<ObjectBuffersWrapper> object_ptr)
        : AbstractShaderRenderer(camera_ptr, shader_ptr), object_ptr(object_ptr) {
}

void ObjectRenderer::render(GLFWwindow *window) {
    glfwGetFramebufferSize(window, &width, &height);
    glUseProgram(shader_ptr->get_program());

    render_internal(window);
//    std::cout << glGetError() << std::endl;
}


void ObjectRenderer::render_internal(GLFWwindow *window) {
    glUniformMatrix4fv (modl_id, 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv (view_id, 1, GL_FALSE, &camera_ptr->get_view()[0][0]);
    glUniformMatrix4fv (proj_id, 1, GL_FALSE, &camera_ptr->get_proj()[0][0]);
    glBindVertexArray (object_ptr->vao);
    glDrawArrays (GL_TRIANGLES, 0, (GLsizei) object_ptr->length);
}