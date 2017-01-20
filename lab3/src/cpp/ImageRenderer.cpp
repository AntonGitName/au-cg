//
// Created by Anton Mordberg on 10/01/2017.
//

#include "ImageRenderer.h"

#define IMAGE_NAME "188"

std::shared_ptr<ObjectBuffersWrapper> ImageRenderer::g_pane = nullptr;
std::shared_ptr<ShaderWrapper> ImageRenderer::g_shader = nullptr;

ImageRenderer::ImageRenderer(const std::shared_ptr<AbstractCamera> &camera_ptr)
        : ObjectRenderer(camera_ptr, get_g_shader(), get_g_pane())
        , AbstractShaderRenderer(camera_ptr, get_g_shader()) {
    glGenTextures(1, &texture_id);

    int width, height;
    unsigned char* image;

    glUseProgram(shader_ptr->get_program());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    image = SOIL_load_image("obj/"IMAGE_NAME".png", &width, &height, 0, SOIL_LOAD_AUTO);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);
    glUniform1i(get_uniform("the_texture"), 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenTextures(1, &normalmap_id);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, normalmap_id);
    image = SOIL_load_image("obj/"IMAGE_NAME"_norm.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);
    glUniform1i(get_uniform("normalmap"), 1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    model = glm::translate(model, glm::vec3(0, 0, -1));
    model = glm::scale(model, glm::vec3(4));
}

void ImageRenderer::init() {
    g_pane = std::make_shared<ObjectBuffersWrapper>(LoadedObject("obj/pane.obj"), true, true);
    g_shader = std::make_shared<ShaderWrapper>(std::vector<std::pair<std::string, GLenum> >(
            {{"shaders/phong_bump_vs.glsl", GL_VERTEX_SHADER},
             {"shaders/phong_bump_fs.glsl", GL_FRAGMENT_SHADER}}));
}

std::shared_ptr<ObjectBuffersWrapper> ImageRenderer::get_g_pane() {
    if (!g_pane) {
        init();
    }
    return g_pane;
}

std::shared_ptr<ShaderWrapper> ImageRenderer::get_g_shader() {
    if (!g_shader) {
        init();
    }
    return g_shader;
}

ImageRenderer::~ImageRenderer() {
    glDeleteTextures(1, &texture_id);
    glDeleteTextures(1, &normalmap_id);
}

void ImageRenderer::setup_render(GLFWwindow *window) {
    AbstractShaderRenderer::setup_render(window);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, normalmap_id);
}

#undef IMAGE_NAME