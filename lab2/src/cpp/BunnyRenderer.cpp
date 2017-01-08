//
// Created by antonpp on 06.01.17.
//

#include "BunnyRenderer.h"

BunnyRenderer::BunnyRenderer(ShaderWrapper shaderWrapper) : pane(4, 4) {
    program_id = shaderWrapper.get_program();

    locationMatrixID = glGetUniformLocation(program_id, "MVP");
    transformID = glGetUniformLocation(program_id, "TRANSFORM");
    imageSpaceWidthHeightID = glGetUniformLocation(program_id, "DIMENSIONS");
    maxIterationsID = glGetUniformLocation(program_id, "FACTORIAL_ITERATIONS");

    transform = glm::mat3(1.0f);

    custom_texture = std::make_shared<MandelbrotTexture>(fractal_iterations);
    glUniform1i(glGetUniformLocation(program_id, "TEXTURE"), 0);

    glUseProgram(program_id);
}

void BunnyRenderer::render(GLFWwindow *window) {
    glfwGetFramebufferSize(window, &width, &height);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = glm::lookAt(
            glm::vec3(0, 0, 3),
            glm::vec3(0, 0, 0),
            glm::vec3(0, 1, 0)
    );

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) (4.0 / 3.0), 0.1f, 100.0f);

    glm::mat4 MVPmatrix = projection * view;


    glfwSwapBuffers(window);
}

void BunnyRenderer::onMouseWheel(double xoffset, double yoffset) {
}

void BunnyRenderer::onWindowSizeChanged(int width, int height) {
    glViewport(0, 0, width, height);
    this->width = width;
    this->height = height;
}

void BunnyRenderer::onMouseButton(int button, int action, int mods) {
}

void BunnyRenderer::onMousePos(double x, double y) {
}

void BunnyRenderer::onKeyEvent(int key, int scancode, int action, int mods) {

}
