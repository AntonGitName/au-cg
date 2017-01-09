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

class ObjectRenderer : public AbstractRenderer {
public:
    ObjectRenderer(std::shared_ptr<AbstractCamera> camera_ptr, ObjectBuffersWrapper object, ShaderWrapper shader);

    void render(GLFWwindow *window);

private:
    GLint view_id;
    std::shared_ptr<AbstractCamera> camera_ptr;
protected:
    GLint model_id;
    glm::mat4 model;

    int width = 0;
    int height = 0;

    ShaderWrapper shader;
    ObjectBuffersWrapper object;
};


#endif //AU_CG_OBJECTRENDERER_H
