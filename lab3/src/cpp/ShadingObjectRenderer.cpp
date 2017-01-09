//
// Created by antonpp on 09.01.17.
//

#include "ShadingObjectRenderer.h"

ShadingObjectRenderer::ShadingObjectRenderer(std::shared_ptr<AbstractCamera> camera_ptr)
        : ObjectRenderer(camera_ptr,
                         std::make_shared<ShaderWrapper>(std::vector<std::pair<std::string, GLenum> >(
                                {{"shaders/phong_vs.glsl", GL_VERTEX_SHADER},
                                 {"shaders/phong_fs.glsl", GL_FRAGMENT_SHADER}})),
                         std::make_shared<ObjectBuffersWrapper>(LoadedObject("obj/suzanne.obj"), true, false)) {

    glUniformMatrix4fv(glGetUniformLocation(shader_ptr->get_program(), "projectionMatrix"), 1, GL_FALSE, &camera_ptr->get_proj()[0][0]);
}

void ShadingObjectRenderer::add_light(std::shared_ptr<LightingSphere> light) {
    lights.push_back(light);
    update_lights_info();
}

void ShadingObjectRenderer::render_internal(GLFWwindow *window) {
    update_lights_position();
    auto model_view = camera_ptr->get_view() * model;
    glm::mat4 normal = glm::inverse(glm::transpose(model_view));
    glUniformMatrix4fv(glGetUniformLocation(shader_ptr->get_program(), "modelViewMatrix"), 1, GL_FALSE, &model_view[0][0]);
    glUniformMatrix3fv(glGetUniformLocation(shader_ptr->get_program(), "normalMatrix"), 1, GL_FALSE, &glm::mat3(normal)[0][0]);

    ObjectRenderer::render_internal(window);
}

template<class T>
void f(T v) {
    std::cout << v.x << " " << v.y << " " << v.z << std::endl;
}


void ShadingObjectRenderer::update_lights_position() {
    std::vector<glm::vec4> positions;
    for (auto light : lights) {
        positions.push_back(light->position);

    }
    glUniform4fv(glGetUniformLocation(shader_ptr->get_program(), "lightPosition"), (GLsizei) lights.size(),
                 (const GLfloat *) positions.data());
    f(lights[0]->position);
}

void ShadingObjectRenderer::update_lights_info() {
    GLint num = (GLint) lights.size();
    glUniform1i(glGetUniformLocation(shader_ptr->get_program(), "lights_num"), num);
    std::vector<glm::vec4> info;

    for (auto light : lights) {
        info.push_back(light->color);
    }
    glUniform4fv(glGetUniformLocation(shader_ptr->get_program(), "Ld"), num , (const GLfloat *) info.data());

    info.clear();
    for (auto light : lights) {
        info.push_back(light->ka);
    }
    glUniform4fv(glGetUniformLocation(shader_ptr->get_program(), "Ka"), num , (const GLfloat *) info.data());

    info.clear();
    for (auto light : lights) {
        info.push_back(light->kd);
    }
    glUniform4fv(glGetUniformLocation(shader_ptr->get_program(), "Kd"), num , (const GLfloat *) info.data());

    info.clear();
    for (auto light : lights) {
        info.push_back(light->ks);
    }
    glUniform4fv(glGetUniformLocation(shader_ptr->get_program(), "Ks"), num , (const GLfloat *) info.data());

    std::vector<GLfloat > ns;
    for (auto light : lights) {
        ns.push_back(light->ns);
    }
    glUniform1fv(glGetUniformLocation(shader_ptr->get_program(), "Ns"), num, ns.data());
}