//
// Created by antonpp on 20.01.17.
//

#include "PhongRenderer.h"


void PhongRenderer::add_light(std::shared_ptr<PointLightInfo> light) {
    lights.insert(light);
    update_lights_info();
}

void PhongRenderer::update_lights_position() {
    std::vector<glm::vec3> positions;
    for (auto light : lights) {
        positions.push_back(light->position);
    }

    glUniform3fv(get_uniform("light_position"), (GLsizei) positions.size(), (const GLfloat *) positions.data());
}

void PhongRenderer::update_lights_info() {
    use_program();

    GLint num = (GLint) lights.size();

    glUniform1i(get_uniform("lights_num"), num);


    std::vector<glm::vec3> info;
    for (auto light : lights) {
        info.push_back(light->specular_color);
    }
    glUniform3fv(get_uniform("specular_color"), num, (const GLfloat *) info.data());

    info.clear();
    for (auto light : lights) {
        info.push_back(light->specular_coef);
    }
    glUniform3fv(get_uniform("specular_coef"), num, (const GLfloat *) info.data());

    info.clear();
    for (auto light : lights) {
        info.push_back(light->diffuse_color);
    }
    glUniform3fv(get_uniform("diffuse_color"), num, (const GLfloat *) info.data());

    info.clear();
    for (auto light : lights) {
        info.push_back(light->diffuse_coef);
    }
    glUniform3fv(get_uniform("diffuse_coef"), num, (const GLfloat *) info.data());

    std::vector<GLfloat> ns;
    for (auto light : lights) {
        ns.push_back(light->specular_exponent);
    }
    glUniform1fv(get_uniform("specular_exponent"), num, ns.data());
}

void PhongRenderer::remove_light(std::shared_ptr<PointLightInfo> light) {
    lights.erase(light);
    update_lights_info();
}

PhongRenderer::PhongRenderer(const std::shared_ptr<AbstractCamera> &camera_ptr,
                             const std::shared_ptr<ShaderWrapper> &shader_ptr)
        : AbstractShaderRenderer(camera_ptr, shader_ptr) {}

void PhongRenderer::setup_render(GLFWwindow *window) {
    AbstractShaderRenderer::setup_render(window);
    update_lights_position();
    auto model_view = camera_ptr->get_view() * model;
    glm::mat4 normal = glm::transpose(glm::inverse(model_view));
    glUniformMatrix4fv(get_uniform("modelViewMatrix"), 1, GL_FALSE, &model_view[0][0]);
    glUniformMatrix3fv(get_uniform("normalMatrix"), 1, GL_FALSE, &glm::mat3(normal)[0][0]);
}
