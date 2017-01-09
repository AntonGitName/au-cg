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

protected:
    GLint proj_id;
    GLint view_id;
    GLint modl_id;
    std::shared_ptr<AbstractCamera> camera_ptr;
    std::shared_ptr<ShaderWrapper> shader_ptr;
    glm::mat4 model;
};


#endif //AU_CG_ABSTRACTSHADERRENDERER_H
