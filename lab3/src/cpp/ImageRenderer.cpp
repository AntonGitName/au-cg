//
// Created by Anton Mordberg on 10/01/2017.
//

#include "ImageRenderer.h"

ImageRenderer::ImageRenderer(const std::shared_ptr<AbstractCamera> &camera_ptr)
        : ObjectRenderer(camera_ptr, get_g_shader(), get_g_pane()) {
// Load textures
    glGenTextures(1, &texture_id);

    int width, height;
    unsigned char* image;

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    image = SOIL_load_image("obj/hypno.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);
    glUniform1i(glGetUniformLocation(shader_ptr->get_program(), "the_texture"), 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void ImageRenderer::init() {
    g_pane = std::make_shared<ObjectBuffersWrapper>(LoadedObject("obj/pane.obj"), true, false);
    g_shader = std::make_shared<ShaderWrapper>(std::vector<std::pair<std::string, GLenum> >(
            {{"shaders/inage_vs.glsl", GL_VERTEX_SHADER},
             {"shaders/image_fs.glsl", GL_FRAGMENT_SHADER}}));
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

void ImageRenderer::render_internal(GLFWwindow *window) {
    ObjectRenderer::render_internal(window);
}
