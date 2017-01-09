//
// Created by antonpp on 06.01.17.
//

#ifndef AU_CG_RENDERER_H
#define AU_CG_RENDERER_H

// opengl
#include <GLFW/glfw3.h>

class AbstractRenderer {
public:
    virtual ~AbstractRenderer() {}

    virtual void render(GLFWwindow *window) = 0;
};


#endif //AU_CG_RENDERER_H
