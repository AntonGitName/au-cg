//
// Created by antonpp on 07.01.17.
//

#ifndef AU_CG_ABSTRACTLISTENER_H
#define AU_CG_ABSTRACTLISTENER_H

// opengl
#include <GLFW/glfw3.h>

struct AbstractWindowListener {
    virtual ~AbstractWindowListener() {}
    virtual void onMouseWheel(double xoffset, double yoffset) = 0;
    virtual void onWindowSizeChanged(int width, int height) = 0;
    virtual void onMouseButton(int button, int action, int mods) = 0;
    virtual void onMousePos(double x, double y) = 0;
    virtual void onKeyEvent(int key, int scancode, int action, int mods) = 0;
};


#endif //AU_CG_ABSTRACTLISTENER_H
