//
// Created by antonpp on 09.01.17.
//

#include "LightingSphereRenderer.h"

std::shared_ptr<ObjectBuffersWrapper> LightingSphereRenderer::g_sphere = nullptr;
std::shared_ptr<ShaderWrapper> LightingSphereRenderer::g_shader = nullptr;

namespace {
    float get_random(float a = 0, float b = 1) {
        auto x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        return x * (b - a) + a;
    }

    glm::vec3 get_random_vec3(float a = 0, float b = 1) {
        return {get_random(a, b), get_random(a, b), get_random(a, b)};
    }
}

LightingSphereRenderer::LightingSphereRenderer(const std::shared_ptr<AbstractCamera> &camera_ptr)
        : ObjectRenderer(camera_ptr, get_g_shader(), get_g_sphere())
        , AbstractShaderRenderer(camera_ptr, get_g_shader()) {
    v0 = get_random_vec3(-5, 5);
    v0.z = -5.f;
//    v0.z = get_random(0, 2);

    freq = get_random_vec3(0.1, 0.5);
    scale = glm::scale(glm::mat4(1), glm::vec3(0.1f));
    amplitude = get_random_vec3(1, 40);
    amplitude.z = 0;

    PointLightInfo light_info;
    auto color = get_random_vec3(0.3, 1);
    light_info.diffuse_color = color;
    light_info.specular_color = color;
    light_info.diffuse_coef = glm::vec3(get_random(0.3, 1));
    light_info.specular_coef = glm::vec3(get_random(0.3, 1));
    light_info.specular_exponent = 200;

    light_info_ptr = std::make_shared<PointLightInfo>(light_info);

    update_position();
}

void LightingSphereRenderer::update_position() {
    t += WindowWrapper::get_delta_time();
    model = glm::translate(scale, v0 + amplitude * glm::sin(freq * t));
    position = camera_ptr->get_view() * model * glm::vec4(0, 0 , 0, 1);
    light_info_ptr->position = glm::vec3(position);
}

void LightingSphereRenderer::init() {
    g_sphere = ObjectBuffersWrapper::load("sphere.obj", true, false);
    g_shader = ShaderWrapper::create("sphere_vs.glsl", "sphere_fs.glsl");
}

std::shared_ptr<ObjectBuffersWrapper> LightingSphereRenderer::get_g_sphere() {
    if (!g_sphere) {
        init();
    }
    return g_sphere;
}

std::shared_ptr<ShaderWrapper> LightingSphereRenderer::get_g_shader() {
    if (!g_shader) {
        init();
    }
    return g_shader;
}

void LightingSphereRenderer::setup_render(GLFWwindow *window) {
    ObjectRenderer::setup_render(window);
    update_position();
    glUniform3fv(get_uniform("sphere_color"), 1, &light_info_ptr->diffuse_color[0]);
}
