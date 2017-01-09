//
// Created by antonpp on 06.01.17.
//

#include "MandelbrotRenderer.h"

MandelbrotRenderer::MandelbrotRenderer(ShaderWrapper shaderWrapper) : pane(1, 1) {
    program_id = shaderWrapper.get_program();

    mvp_id = glGetUniformLocation(program_id, "MVP");
    transform_id = glGetUniformLocation(program_id, "TRANSFORM");
    fractal_iterations_id = glGetUniformLocation(program_id, "FACTORIAL_ITERATIONS");

    transform = glm::mat4(10.f);
    view = glm::lookAt(
            glm::vec3(0, 0, 5),
            glm::vec3(0, 0, 0),
            glm::vec3(0, 1, 0)
    );

    custom_texture = std::make_shared<MandelbrotTexture>(fractal_iterations);
    glUniform1i(glGetUniformLocation(program_id, "TEXTURE"), 0);

    glUseProgram(program_id);
}

void MandelbrotRenderer::render(GLFWwindow *window) {
    glfwGetFramebufferSize(window, &width, &height);

    auto model = glm::scale(glm::mat4(1), glm::vec3(23, 23, 23));
    auto projection = glm::perspective(glm::radians(45.0f), ((float) width / height), 0.01f, 1000.0f);
    auto MVPmatrix = projection * view * model;

    glUniformMatrix4fv(mvp_id, 1, GL_FALSE, &MVPmatrix[0][0]);
    glUniformMatrix4fv(transform_id, 1, GL_FALSE, &transform[0][0]);
    glUniform1i(fractal_iterations_id, fractal_iterations);

    pane.draw();
}

void MandelbrotRenderer::onMouseWheel(double xoffset, double yoffset) {
    float zoom_factor = (float) pow(1.1, -yoffset);
    float dx = (float) ((width / 2 - cursor_x) * 1.35 / width);
    float dy = (float) ((height / 2 - cursor_y) * 1.00 / height);

    transform = glm::translate(transform, glm::vec3(-dx, dy, 0));

    transform = glm::scale(transform, glm::vec3(zoom_factor, zoom_factor, zoom_factor));

    transform = glm::translate(transform, glm::vec3(dx, -dy, 0));
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
        float dx = (float) ((x - cursor_x) * 1.35 / width);
        float dy = (float) ((y - cursor_y) * 1.00 / height);

        transform = glm::translate(transform, glm::vec3(-dx, dy, 0));
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
        case GLFW_KEY_UP:
            ++fractal_iterations;
            break;
        case GLFW_KEY_DOWN:
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
