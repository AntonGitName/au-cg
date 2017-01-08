//
// Created by antonpp on 06.01.17.
//

#include "BunnyRenderer.h"

MandelbrotRenderer::MandelbrotRenderer(ShaderWrapper shaderWrapper) : pane(4, 4) {
    program_id = shaderWrapper.get_program();

    mvp_id = glGetUniformLocation(program_id, "MVP");
    transform_id = glGetUniformLocation(program_id, "TRANSFORM");
    dimensions_id = glGetUniformLocation(program_id, "DIMENSIONS");
    fractal_iterations_id = glGetUniformLocation(program_id, "FACTORIAL_ITERATIONS");

    transform = glm::mat3(1.0f);

    custom_texture = std::make_shared<MandelbrotTexture>(fractal_iterations);
    glUniform1i(glGetUniformLocation(program_id, "TEXTURE"), 0);

    glUseProgram(program_id);
}

void MandelbrotRenderer::render(GLFWwindow *window) {
    glfwGetFramebufferSize(window, &width, &height);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = glm::lookAt(
            glm::vec3(0, 0, 3),
            glm::vec3(0, 0, 0),
            glm::vec3(0, 1, 0)
    );

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) (4.0 / 3.0), 0.1f, 100.0f);

    glm::mat4 MVPmatrix = projection * view;

    glUniformMatrix4fv(mvp_id, 1, GL_FALSE, &MVPmatrix[0][0]);
    glUniformMatrix3fv(transform_id, 1, GL_FALSE, &transform[0][0]);

    glUniform2f(dimensions_id, pane.get_width(), pane.get_height());
    glUniform1i(fractal_iterations_id, fractal_iterations);

    pane.draw();

    glfwSwapBuffers(window);
}

void MandelbrotRenderer::onMouseWheel(double xoffset, double yoffset) {
    float zoom_factor = (float) pow(1.1, -yoffset);
    transform[0][0] *= zoom_factor;
    transform[1][1] *= zoom_factor;
}

void MandelbrotRenderer::onWindowSizeChanged(int width, int height) {
    glViewport(0, 0, width, height);
    this->width = width;
    this->height = height;
}

void MandelbrotRenderer::onMouseButton(int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        isMousePressed = action == GLFW_PRESS;
    }
}

void MandelbrotRenderer::onMousePos(double x, double y) {
    if (isMousePressed) {
        float dx = pane.get_width() * (float) (x - cursor_x) / width;
        float dy = pane.get_height() * (float) (y - cursor_y) / height;

        transform[2][0] += dx * transform[0][0];
        transform[2][1] -= dy * transform[0][0];
    }
    cursor_x = (float) x;
    cursor_y = (float) y;
}

void MandelbrotRenderer::onKeyEvent(int key, int scancode, int action, int mods) {
    auto prev_iter = fractal_iterations;
    if (action == GLFW_RELEASE) {
        return;
    }

    switch (key) {
        case GLFW_KEY_EQUAL:
            ++fractal_iterations;
            break;
        case GLFW_KEY_MINUS:
            --fractal_iterations;
            break;
        default:
            return;
    }
    fractal_iterations = std::max(1, fractal_iterations);
    fractal_iterations = std::min(1000, fractal_iterations);

    if (prev_iter != fractal_iterations) {
        custom_texture = std::make_shared<MandelbrotTexture>(fractal_iterations);
        glUniform1i(glGetUniformLocation(program_id, "TEXTURE"), 0);
    }
}
