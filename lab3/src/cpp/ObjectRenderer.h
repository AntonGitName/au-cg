//
// Created by antonpp on 08.01.17.
//

#ifndef AU_CG_OBJECTRENDERER_H
#define AU_CG_OBJECTRENDERER_H

// opengl
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

// std
#include <memory>

// local
#include "AbstractRenderer.h"
#include "ShaderWrapper.h"
#include "AbstractWindowListener.h"
#include "LoadedObject.h"
#include "ObjectBuffersWrapper.h"
#include "AbstractCamera.h"
#include "AbstractShaderRenderer.h"

class ObjectRenderer : public AbstractShaderRenderer {
public:
    ObjectRenderer(std::shared_ptr<AbstractCamera> camera_ptr,
                   std::shared_ptr<ShaderWrapper> shader_ptr,
                   std::shared_ptr<ObjectBuffersWrapper> object_ptr);

    void render(GLFWwindow *window) final;

protected:
    virtual void render_internal(GLFWwindow *window);

private:
    std::shared_ptr<ObjectBuffersWrapper> object_ptr;
};


#endif //AU_CG_OBJECTRENDERER_H
