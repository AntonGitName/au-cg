//
// Created by antonpp on 09.01.17.
//

#include "LightingSphere.h"

std::shared_ptr<ObjectBuffersWrapper> LightingSphere::g_sphere = nullptr;
std::shared_ptr<ShaderWrapper> LightingSphere::g_shader = nullptr;

namespace {
    float get_random(float a = 0, float b = 1) {
        auto x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        return x * (b - a) + a;
    }
}

LightingSphere::LightingSphere(const std::shared_ptr<AbstractCamera> &camera_ptr)
        : ObjectRenderer(camera_ptr, get_g_shader(), get_g_sphere()) {

    color = {get_random(0, 1), get_random(0, 1), get_random(0, 1)};

    v0 = {get_random(-1, 10), get_random(-1, 10), get_random(-1, 10)};
    freq = {get_random(-1, 1), get_random(-1, 1), get_random(-1, 1)};
    scale = glm::scale(glm::mat4(1), glm::vec3(get_random(0, 1)));
    amplitude = {get_random(0, 5), get_random(0, 5), get_random(0, 5)};

    diffuse  = {get_random(0, 1), get_random(0, 1), get_random(0, 1)};
    specular = {get_random(0, 1), get_random(0, 1), get_random(0, 1)};
}

void LightingSphere::render(GLFWwindow *window) {
    update_position();
    glUniform3fv(glGetUniformLocation(g_shader->get_program(), "sphere_color"), 1, &color[0]);
    model = glm::translate(scale, position);
    ObjectRenderer::render(window);
}

void LightingSphere::update_position() {
//    t += dt;
    position = v0 + amplitude * glm::sin(freq * t);
//    model = glm::translate(scale, position);
    model = glm::mat4(1);
}

GLuint LightingSphere::get_vao() const {
    return object_ptr->vao;
}

size_t LightingSphere::get_length() const {
    return object_ptr->length;
}

void LightingSphere::init() {
    g_sphere = std::make_shared<ObjectBuffersWrapper>(LoadedObject("obj/sphere.obj"), true, false);
    g_shader = std::make_shared<ShaderWrapper>(std::vector<std::pair<std::string, GLenum> >(
            {{"shaders/point_light_vs.glsl", GL_VERTEX_SHADER},
             {"shaders/point_light_fs.glsl", GL_FRAGMENT_SHADER}}));

}

std::shared_ptr<ObjectBuffersWrapper> LightingSphere::get_g_sphere() {
    if (!g_sphere) {
        init();
    }
    return g_sphere;
}

std::shared_ptr<ShaderWrapper> LightingSphere::get_g_shader() {
    if (!g_shader) {
        init();
    }
    return g_shader;
}
