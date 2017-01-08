//
// Created by antonpp on 06.01.17.
//

#include "BunnyRenderer.h"

BunnyRenderer::BunnyRenderer() : bunny(LoadedObject("obj/bunny_with_normals.obj"), true, false) {
    auto shaderWrapper = ShaderWrapper({{"shaders/bunny_vs.glsl", GL_VERTEX_SHADER},
                                        {"shaders/bunny_fs.glsl", GL_FRAGMENT_SHADER}});

    program_id = shaderWrapper.get_program();

    model_mat_id = glGetUniformLocation(program_id, "M");
    view_mat_id = glGetUniformLocation(program_id, "V");
    projection_mat_id = glGetUniformLocation(program_id, "P");

    model = glm::mat4(1);
    view = view = glm::lookAt(
            glm::vec3(0, 0, 3),
            glm::vec3(0, 0, 0),
            glm::vec3(0, 1, 0)
    );
    projection = glm::perspective(45.0f, 4.0f/3.0f, 0.1f, 100.0f);


    glEnable (GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"
    glEnable (GL_CULL_FACE); // cull face
    glCullFace (GL_BACK); // cull back face
    glFrontFace (GL_CCW); // set counter-clock-wise vertex order to mean the front
    glClearColor (0.2, 0.2, 0.2, 1.0); // grey background
    glViewport (0, 0, width, height);
}

void BunnyRenderer::render(GLFWwindow *window) {
    glfwGetFramebufferSize(window, &width, &height);

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram (program_id);


    glUniformMatrix4fv (model_mat_id, 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv (view_mat_id, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv (projection_mat_id, 1, GL_FALSE, &projection[0][0]);

    glBindVertexArray(bunny.vao);
    glDrawArrays (GL_TRIANGLES, 0, bunny.length);

    // Swap buffers
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
