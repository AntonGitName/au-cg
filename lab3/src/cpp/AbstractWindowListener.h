//
// Created by antonpp on 07.01.17.
//

#ifndef AU_CG_ABSTRACTLISTENER_H
#define AU_CG_ABSTRACTLISTENER_H

// opengl
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct AbstractWindowListener {
    virtual ~AbstractWindowListener() {}
    virtual void onMouseWheel(double xoffset, double yoffset) {}
    virtual void onWindowSizeChanged(int width, int height) {}
    virtual void onMouseButton(int button, int action, int mods) {}
    virtual void onMousePos(double x, double y) {}
    virtual void onKeyEvent(int key, int scancode, int action, int mods) {}
};


#endif //AU_CG_ABSTRACTLISTENER_H
