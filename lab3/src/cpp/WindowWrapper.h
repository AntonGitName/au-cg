//
// Created by antonpp on 06.01.17.
//

#ifndef AU_CG_WINDOWWRAPPER_H
#define AU_CG_WINDOWWRAPPER_H

// opengl
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// std
#include <string>
#include <stdexcept>
#include <vector>
#include <map>
#include <memory>

// local
#include "AbstractRenderer.h"
#include "AbstractWindowListener.h"


class WindowWrapper {
public:

    WindowWrapper(int w, int h, const char* title);
    ~WindowWrapper();

    GLFWwindow * get_window() const;

    void loop();

    void add_renderer(std::shared_ptr<AbstractRenderer> renderer);
    void reset_renderers();
    void add_listener(std::shared_ptr<AbstractWindowListener> listener);

private:
    GLFWwindow *window;
    std::vector<std::shared_ptr<AbstractRenderer>> renderers;
    void show_fps();
    
    static std::map<GLFWwindow *, std::vector<std::shared_ptr<AbstractWindowListener> > > gListeners;

    static void add_listener(GLFWwindow *, std::shared_ptr<AbstractWindowListener> listener);

    static void onMouseWheel(GLFWwindow *window, double xoffset, double yoffset);
    static void onWindowSizeChanged(GLFWwindow* window, int width, int height);
    static void onMouseButton(GLFWwindow *window, int button, int action, int mods);
    static void onMousePos(GLFWwindow *window, double x, double y);
    static void onKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);

    double prev_time = 0;
    int shown_frames = 0;
    std::string title;
};


#endif //AU_CG_WINDOWWRAPPER_H
