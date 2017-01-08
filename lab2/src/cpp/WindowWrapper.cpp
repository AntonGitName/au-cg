//
// Created by antonpp on 06.01.17.
//

#include <ostream>
#include <iostream>
#include "WindowWrapper.h"

std::map<GLFWwindow *, std::vector<AbstractWindowListener*> > WindowWrapper::gListeners;

WindowWrapper::WindowWrapper(int w, int h, const char* title) : title(title) {
    if (!glfwInit()) {
        throw std::runtime_error("Could not init glfw");
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (!(window = glfwCreateWindow(w, h, title, NULL, NULL))) {
        glfwTerminate();
        throw std::runtime_error("Could not create window");
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("Could not init glew");
    }
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // it is useful sometimes to find bugs with black objects
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

    glfwSetFramebufferSizeCallback(window, WindowWrapper::onWindowSizeChanged);
    glfwSetCursorPosCallback(window, WindowWrapper::onMousePos);
    glfwSetScrollCallback(window, WindowWrapper::onMouseWheel);
    glfwSetKeyCallback(window, WindowWrapper::onKeyEvent);
    glfwSetMouseButtonCallback(window, WindowWrapper::onMouseButton);
}

WindowWrapper::~WindowWrapper() {
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

GLFWwindow* WindowWrapper::get_window() const {
    return window;
}

void WindowWrapper::loop() {
    for (;;) {

        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (auto renderer: renderers) {
            renderer->render(window);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

        show_fps();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(window)) {
            break;
        }
    }
}

void WindowWrapper::add_renderer(AbstractRenderer *renderer) {
    renderers.push_back(renderer);
}

void WindowWrapper::add_listener(GLFWwindow *window, AbstractWindowListener *listener) {
    gListeners[window].push_back(listener);
}

void WindowWrapper::onMouseWheel(GLFWwindow *window, double xoffset, double yoffset) {
    for (auto listener : gListeners[window]) {
        listener->onMouseWheel(xoffset, yoffset);
    }
}

void WindowWrapper::onWindowSizeChanged(GLFWwindow *window, int width, int height) {
    for (auto listener : gListeners[window]) {
        listener->onWindowSizeChanged(width, height);
    }
}

void WindowWrapper::onMouseButton(GLFWwindow *window, int button, int action, int mods) {
    for (auto listener : gListeners[window]) {
        listener->onMouseButton(button, action, mods);
    }
}

void WindowWrapper::onMousePos(GLFWwindow *window, double x, double y) {
    for (auto listener : gListeners[window]) {
        listener->onMousePos(x, y);
    }
}

void WindowWrapper::onKeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods) {
    for (auto listener : gListeners[window]) {
        listener->onKeyEvent(key, scancode, action, mods);
    }
}

void WindowWrapper::show_fps() {
    double current_time = glfwGetTime();
    auto elapsed_time = current_time - prev_time;
    if (elapsed_time > 1.0) {
        prev_time = current_time;
        double fps = (double) shown_frames / elapsed_time;
        char tmp[256];
        sprintf (tmp, "%s. FPS = %.2f", title.c_str(), fps);
        glfwSetWindowTitle (window, tmp);
        shown_frames = 0;
    }
    shown_frames++;

}
