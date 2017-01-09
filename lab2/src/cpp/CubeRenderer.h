//
// Created by antonpp on 08.01.17.
//

#ifndef AU_CG_CUBERENDERER_H
#define AU_CG_CUBERENDERER_H

// opengl
#include <SOIL/SOIL.h>

// local
#include "ObjectRenderer.h"

class CubeRenderer : public ObjectRenderer {
public:
    CubeRenderer(std::shared_ptr<Camera> camera_ptr);
    ~CubeRenderer();

    void render(GLFWwindow *window);

private:
    void load_cubemap();

    GLuint cubemap_id = (GLuint) -1;
};


#endif //AU_CG_CUBERENDERER_H
