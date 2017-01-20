//
// Created by antonpp on 09.01.17.
//

#ifndef AU_CG_ABSTRACTSHADERRENDERER_H
#define AU_CG_ABSTRACTSHADERRENDERER_H


// opengl
#include <GL/glew.h>

// std
#include <memory>

// local
#include "AbstractRenderer.h"
#include "AbstractCamera.h"
#include "ShaderWrapper.h"

class AbstractShaderRenderer : public AbstractRenderer {
public:
    AbstractShaderRenderer(std::shared_ptr<AbstractCamera> camera_ptr, std::shared_ptr<ShaderWrapper> shader_ptr);

    void render(GLFWwindow *window) final;

protected:
    void use_program();

    virtual void render_internal(GLFWwindow *window) = 0;
    virtual void setup_render(GLFWwindow *window);

    std::shared_ptr<AbstractCamera> camera_ptr;
    std::shared_ptr<ShaderWrapper> shader_ptr;
    glm::mat4 model;

    GLint get_uniform(const char* name);
};


#endif //AU_CG_ABSTRACTSHADERRENDERER_H
