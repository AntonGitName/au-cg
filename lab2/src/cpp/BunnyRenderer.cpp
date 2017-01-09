//
// Created by antonpp on 06.01.17.
//

#include "BunnyRenderer.h"

BunnyRenderer::BunnyRenderer(std::shared_ptr<AbstractCamera> camera_ptr)
        : ObjectRenderer(camera_ptr,
                         ObjectBuffersWrapper(LoadedObject("obj/bunny_with_normals.obj"), true, false),
                         ShaderWrapper({{"shaders/bunny_vs.glsl", GL_VERTEX_SHADER},
                                        {"shaders/bunny_fs.glsl", GL_FRAGMENT_SHADER}})) {
    model = glm::scale(model, glm::vec3(10, 10, 10));
}
