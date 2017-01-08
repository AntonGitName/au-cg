//
// Created by antonpp on 06.01.17.
//

#include "WindowWrapper.h"

std::map<GLFWwindow *, std::vector<AbstractWindowListener*> > WindowWrapper::gListeners;

WindowWrapper::WindowWrapper(int w, int h, const char* title) {
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

        for (auto renderer: renderers) {
            renderer->render(window);
        }

        glfwPollEvents();

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