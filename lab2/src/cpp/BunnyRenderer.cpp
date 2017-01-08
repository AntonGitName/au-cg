//
// Created by antonpp on 06.01.17.
//

#include "BunnyRenderer.h"

BunnyRenderer::BunnyRenderer() : bunny(LoadedObject("obj/bunny_with_normals.obj"), true, false) {
    auto shaderWrapper = ShaderWrapper({{"shaders/bunny_vs.glsl", GL_VERTEX_SHADER}});

    program_id = shaderWrapper.get_program();

    model_M = glGetUniformLocation(program_id, "M");
    model_mat = glm::mat4(1);
}

void BunnyRenderer::render(GLFWwindow *window) {
    glfwGetFramebufferSize(window, &width, &height);

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glUseProgram (program_id);
    glBindVertexArray (bunny.vao);
    glUniformMatrix4fv (model_M, 1, GL_FALSE, &model_mat[0][0]);
    glDrawArrays (GL_TRIANGLES, 0, bunny.length);

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
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
