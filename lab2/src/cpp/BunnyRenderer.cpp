//
// Created by antonpp on 06.01.17.
//

#include "BunnyRenderer.h"

BunnyRenderer::BunnyRenderer()
        : ObjectRenderer(ObjectBuffersWrapper(LoadedObject("obj/bunny_with_normals.obj"), true, false),
                         ShaderWrapper({{"shaders/bunny_vs.glsl", GL_VERTEX_SHADER},
                                        {"shaders/bunny_fs.glsl", GL_FRAGMENT_SHADER}})) {
}

void BunnyRenderer::onMouseWheel(double xoffset, double yoffset) {
}

void BunnyRenderer::onWindowSizeChanged(int width, int height) {
    glViewport(0, 0, width, height);
    this->width = width;
    this->height = height;
}

void BunnyRenderer::onMouseButton(int button, int action, int mods) {
}

void BunnyRenderer::onMousePos(double x, double y) {
}

void BunnyRenderer::onKeyEvent(int key, int scancode, int action, int mods) {

}
