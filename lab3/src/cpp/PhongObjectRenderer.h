//
// Created by antonpp on 09.01.17.
//

#ifndef AU_CG_SHADINGOBJECTRENDERER_H
#define AU_CG_SHADINGOBJECTRENDERER_H


// opengl
#include <SOIL/SOIL.h>

// std
#include <set>

// local
#include "ObjectRenderer.h"
#include "LightingSphereRenderer.h"
#include "PhongRenderer.h"

class PhongObjectRenderer : public PhongRenderer, public ObjectRenderer {
public:
    PhongObjectRenderer(const std::shared_ptr<AbstractCamera> &camera_ptr);
    ~PhongObjectRenderer();

private:
    void setup_render(GLFWwindow *window);
    void render_internal(GLFWwindow *window);

    GLuint texture_id;
};


#endif //AU_CG_SHADINGOBJECTRENDERER_H
