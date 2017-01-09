//
// Created by antonpp on 09.01.17.
//

#include "AbstractShaderRenderer.h"

AbstractShaderRenderer::AbstractShaderRenderer(std::shared_ptr<AbstractCamera> camera_ptr,
                                               std::shared_ptr<ShaderWrapper> shader_ptr)
    : camera_ptr(camera_ptr), shader_ptr(shader_ptr) {

    modl_id = glGetUniformLocation(shader_ptr->get_program(), "M");
    view_id = glGetUniformLocation(shader_ptr->get_program(), "V");
    proj_id = glGetUniformLocation(shader_ptr->get_program(), "P");

    model = glm::mat4(1);

    glUseProgram(shader_ptr->get_program());
    glUniformMatrix4fv(proj_id, 1, GL_FALSE, &camera_ptr->get_proj()[0][0]);
}
