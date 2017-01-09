//
// Created by antonpp on 06.01.17.
//

#ifndef AU_CG_SIMPLERENDERER_H
#define AU_CG_SIMPLERENDERER_H

// opengl
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

// std
#include <memory>

// local
#include "ShaderWrapper.h"
#include "AbstractWindowListener.h"
#include "LoadedObject.h"
#include "ObjectBuffersWrapper.h"
#include "ObjectRenderer.h"


class BunnyRenderer : public ObjectRenderer {
public:
    BunnyRenderer(std::shared_ptr<AbstractCamera> camera_ptr);
};


#endif //AU_CG_SIMPLERENDERER_H
