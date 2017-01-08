//
// Created by antonpp on 06.01.17.
//

#include "BunnyRenderer.h"

BunnyRenderer::BunnyRenderer()
        : bunny(LoadedObject("obj/bunny_with_normals.obj"), true, false)
        , cube(LoadedObject("obj/cube.obj"), true, true)
        , bunny_shader({{"shaders/bunny_vs.glsl", GL_VERTEX_SHADER}, {"shaders/bunny_fs.glsl", GL_FRAGMENT_SHADER}}),
          cube_shader({{"shaders/cube_vs.glsl", GL_VERTEX_SHADER}, {"shaders/cube_fs.glsl", GL_FRAGMENT_SHADER}}) {

    model_cube_id = glGetUniformLocation(cube_shader.get_program(), "M");
    model_bunny_id = glGetUniformLocation(bunny_shader.get_program(), "M");


    model_bunny = model_cube = glm::mat4(1);

    view = glm::lookAt(
            glm::vec3(0, 0, 3),
            glm::vec3(0, 0, 0),
            glm::vec3(0, 1, 0)
    );
    auto projection = glm::perspective(45.0f, 4.0f/3.0f, 0.1f, 100.0f);

    auto programs = {cube_shader.get_program(), bunny_shader.get_program()};
    for (auto program_id : programs) {
        glUseProgram(program_id);
        auto projection_mat_id = glGetUniformLocation(program_id, "P");
        glUniformMatrix4fv (projection_mat_id, 1, GL_FALSE, &projection[0][0]);
    }
}

void BunnyRenderer::render(GLFWwindow *window) {
    glfwGetFramebufferSize(window, &width, &height);

    // cube
    glUseProgram(cube_shader.get_program());
    glUniformMatrix4fv (model_cube_id, 1, GL_FALSE, &model_cube[0][0]);
    glUniformMatrix4fv (view_cube_id, 1, GL_FALSE, &view[0][0]);
    glBindVertexArray (cube.vao);
    glDrawArrays (GL_TRIANGLES, 0, cube.length);

    // bunny
    glUseProgram(bunny_shader.get_program());
    glUniformMatrix4fv (model_bunny_id, 1, GL_FALSE, &model_bunny[0][0]);
    glUniformMatrix4fv (view_bunny_id, 1, GL_FALSE, &view[0][0]);
    glBindVertexArray (bunny.vao);
    glDrawArrays (GL_TRIANGLES, 0, bunny.length);
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
