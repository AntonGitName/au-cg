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


class BunnyRenderer : public ObjectRenderer, public AbstractWindowListener {
public:
    BunnyRenderer();

public:
    void onMouseWheel(double xoffset, double yoffset) override;

    void onWindowSizeChanged(int width, int height) override;

    void onMouseButton(int button, int action, int mods) override;

    void onMousePos(double x, double y) override;

    void onKeyEvent(int key, int scancode, int action, int mods) override;
};


#endif //AU_CG_SIMPLERENDERER_H
