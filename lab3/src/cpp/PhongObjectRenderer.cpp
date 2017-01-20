//
// Created by antonpp on 09.01.17.
//

#include "PhongObjectRenderer.h"

using std::make_shared;

void PhongObjectRenderer::render_internal(GLFWwindow *window) {
    ObjectRenderer::render_internal(window);
}

PhongObjectRenderer::PhongObjectRenderer(const std::shared_ptr<AbstractCamera> &camera_ptr)
        : ObjectRenderer(nullptr, nullptr, ObjectBuffersWrapper::load("alien-mothership.obj", true, true))
        , AbstractShaderRenderer(camera_ptr, ShaderWrapper::create("phong_vs.glsl", "phong_fs.glsl"))
        , PhongRenderer(nullptr, nullptr) {

    glUseProgram(shader_ptr->get_program());
    glUniform1f(get_uniform("gamma"), 2.2);

    glGenTextures(1, &texture_id);

    int width, height;
    unsigned char* image;

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    image = SOIL_load_image("obj/alien-mothership-yellow.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);
    glUniform1i(get_uniform("the_texture"), 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    model = glm::scale(glm::vec3(0.005, 0.005, 0.005));
    model = glm::translate(model, glm::vec3(0, 0, -100));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1, 0, 0));
}

void PhongObjectRenderer::setup_render(GLFWwindow *window) {
    model = glm::rotate(model, -WindowWrapper::get_delta_time() / 4, glm::vec3(0, 1, 0));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    PhongRenderer::setup_render(window);
}

PhongObjectRenderer::~PhongObjectRenderer() {
    glDeleteTextures(1, &texture_id);
}
