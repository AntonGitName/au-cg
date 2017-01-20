//
// Created by antonpp on 08.01.17.
//

#include "ObjectRenderer.h"

ObjectRenderer::ObjectRenderer(std::shared_ptr<AbstractCamera> camera_ptr,
                               std::shared_ptr<ShaderWrapper> shader_ptr,
                               std::shared_ptr<ObjectBuffersWrapper> object_ptr)
        : AbstractShaderRenderer(camera_ptr, shader_ptr), object_ptr(object_ptr) {
}

void ObjectRenderer::render_internal(GLFWwindow *window) {
    glBindVertexArray(object_ptr->vao);
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei) object_ptr->length);
}