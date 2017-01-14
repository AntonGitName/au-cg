//
// Created by antonpp on 09.01.17.
//

#include "LightingSphereRenderer.h"

std::shared_ptr<ObjectBuffersWrapper> LightingSphereRenderer::g_sphere = nullptr;
std::shared_ptr<ShaderWrapper> LightingSphereRenderer::g_shader = nullptr;

float LightingSphereRenderer::dt = 0.05;

namespace {
    float get_random(float a = 0, float b = 1) {
        auto x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        return x * (b - a) + a;
    }

    glm::vec3 get_random_vec3(float a = 0, float b = 1) {
        return {get_random(a, b), get_random(a, b), get_random(a, b)};
    }

    glm::vec4 get_random_vec4(float a = 0, float b = 1) {
        return glm::vec4(get_random_vec3(a, b), 1);
    }
}

template<class T>
void f(T v) {
    std::cout << v.x << " " << v.y << " " << v.z << std::endl;
}

LightingSphereRenderer::LightingSphereRenderer(const std::shared_ptr<AbstractCamera> &camera_ptr)
        : ObjectRenderer(camera_ptr, get_g_shader(), get_g_sphere()) {
    v0 = get_random_vec3(-5, 5);
    freq = get_random_vec3(1, 2);
    scale = glm::scale(glm::mat4(1), glm::vec3(get_random(0.1, 1)));
    amplitude = get_random_vec3(1, 4);

    color = {get_random(0, 1), get_random(0, 1), get_random(0, 1), 1};

    ka = {1.0f, 0.5f, 0.5f, 1.0f};
    kd = {0.8f, 0.8f, 0.8f, 1.0f};
    ks = {0.3f, 0.3f, 0.3f, 1.0f};
    ns = get_random(100, 200);

    update_position();
}

void LightingSphereRenderer::update_position() {
    t += dt;
    model = glm::translate(scale, v0 + amplitude * glm::sin(freq * t));
    position = camera_ptr->get_view() * model * glm::vec4(0, 0 , 0, 1);
}

void LightingSphereRenderer::init() {
    g_sphere = std::make_shared<ObjectBuffersWrapper>(LoadedObject("obj/sphere.obj"), true, false);
    g_shader = std::make_shared<ShaderWrapper>(std::vector<std::pair<std::string, GLenum> >(
            {{"shaders/point_light_vs.glsl", GL_VERTEX_SHADER},
             {"shaders/point_light_fs.glsl", GL_FRAGMENT_SHADER}}));
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

void LightingSphereRenderer::render_internal(GLFWwindow *window) {
    update_position();
    glUniform3fv(glGetUniformLocation(g_shader->get_program(), "sphere_color"), 1, &color[0]);

    ObjectRenderer::render_internal(window);
}

void LightingSphereRenderer::update_speed(bool increase) {
    dt *= increase ? 1 / dt_scale : dt_scale;
}
