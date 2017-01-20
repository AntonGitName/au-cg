//
// Created by antonpp on 20.01.17.
//

#include "PhongTextureRenderer.h"

void PhongTextureRenderer::setup_render(GLFWwindow *window) {
    ImageRenderer::setup_render(window);
    PhongRenderer::setup_render(window);
}

PhongTextureRenderer::PhongTextureRenderer(const std::shared_ptr<AbstractCamera> &camera_ptr)
        : AbstractShaderRenderer(camera_ptr, ImageRenderer::get_g_shader())
        , PhongRenderer(nullptr, nullptr)
        , ImageRenderer(nullptr) {

}
