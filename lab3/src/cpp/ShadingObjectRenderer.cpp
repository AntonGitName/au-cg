//
// Created by antonpp on 09.01.17.
//

#include "ShadingObjectRenderer.h"

ShadingObjectRenderer::ShadingObjectRenderer(std::shared_ptr<AbstractCamera> camera_ptr)
        : camera_ptr(camera_ptr) {
    object_ptr = std::make_shared<ObjectBuffersWrapper>(LoadedObject("obj/suzanne.obj"), true, false);
    geometry_pass = std::make_shared<ShaderWrapper>(std::vector<std::pair<std::string, GLenum> >(
            {{"shaders/first_pass_vs.glsl", GL_VERTEX_SHADER},
             {"shaders/first_pass_fs.glsl", GL_FRAGMENT_SHADER}}));
    light_pass = std::make_shared<ShaderWrapper>(std::vector<std::pair<std::string, GLenum> >(
            {{"shaders/second_pass_vs.glsl", GL_VERTEX_SHADER},
             {"shaders/second_pass_fs.glsl", GL_FRAGMENT_SHADER}}));

    gpass_P_loc = glGetUniformLocation (geometry_pass->get_program(), "P");
    gpass_V_loc = glGetUniformLocation (geometry_pass->get_program(), "V");
    gpass_M_loc = glGetUniformLocation (geometry_pass->get_program(), "M");

    lpass_P_loc = glGetUniformLocation (light_pass->get_program(), "P");
    lpass_V_loc = glGetUniformLocation (light_pass->get_program(), "V");
    lpass_M_loc = glGetUniformLocation (light_pass->get_program(), "M");
    lpass_L_p_loc = glGetUniformLocation (light_pass->get_program(), "lp");
    lpass_L_d_loc = glGetUniformLocation (light_pass->get_program(), "ld");
    lpass_L_s_loc = glGetUniformLocation (light_pass->get_program(), "ls");
    lpass_p_tex_loc = glGetUniformLocation (light_pass->get_program(), "p_tex");
    lpass_n_tex_loc = glGetUniformLocation (light_pass->get_program(), "n_tex");

    lpass_p_tex_loc = glGetUniformLocation (light_pass->get_program(), "p_tex");
    lpass_n_tex_loc = glGetUniformLocation (light_pass->get_program(), "n_tex");

    glUseProgram(geometry_pass->get_program());
    glUniformMatrix4fv(gpass_P_loc, 1, GL_FALSE, &camera_ptr->get_proj()[0][0]);
    glUseProgram(light_pass->get_program());
    glUniformMatrix4fv (lpass_P_loc, 1, GL_FALSE, &camera_ptr->get_proj()[0][0]);
    glUniform1i (lpass_p_tex_loc, 0);
    glUniform1i (lpass_n_tex_loc, 1);
}

void ShadingObjectRenderer::render(GLFWwindow *window) {
    static bool not_init = true;
    glfwGetFramebufferSize(window, &width, &height);
    if (not_init) {
        gb.Init((unsigned int) width, (unsigned int) height);
        not_init = false;
    }
    // first

    gb.BindForWriting();
    glClearColor (0.0f, 0.0f, 0.0f, 1.0f);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable (GL_BLEND);
    glEnable (GL_DEPTH_TEST);
    glDepthMask (GL_TRUE);

    glUseProgram (geometry_pass->get_program());

    glBindVertexArray (object_ptr->vao);
    glUniformMatrix4fv (gpass_M_loc, 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv (gpass_V_loc, 1, GL_FALSE, &camera_ptr->get_view()[0][0]);
    glDrawArrays (GL_TRIANGLES, 0, (GLsizei) object_ptr->length);

    // second

    glBindFramebuffer (GL_FRAMEBUFFER, 0);
    glClearColor (0.2, 0.2, 0.2, 1.0f);
    glClear (GL_COLOR_BUFFER_BIT);

    glEnable (GL_BLEND); // --- could reject background frags!
    glBlendEquation (GL_FUNC_ADD);
    glBlendFunc (GL_ONE, GL_ONE); // addition each time
    glDisable (GL_DEPTH_TEST);
    glDepthMask (GL_FALSE);

    gb.BindForReading();

    glUseProgram (light_pass->get_program());

    /* virtual camera matrices */
    glUniformMatrix4fv (lpass_V_loc, 1, GL_FALSE, &camera_ptr->get_view()[0][0]);

    for (auto &l : lights) {
        l->update_position();

        glBindVertexArray (l->get_vao());
        /* world position */
        glUniform3f (lpass_L_p_loc, l->position.x, l->position.y, l->position.z);
        /* diffuse colour */
        glUniform3f (lpass_L_d_loc, l->diffuse.x, l->diffuse.y, l->diffuse.z);
        /* specular colour */
        glUniform3f (lpass_L_s_loc, l->specular.x, l->specular.y, l->specular.z);

        glUniformMatrix4fv (lpass_M_loc, 1, GL_FALSE, &l->model[0][0]);
        glDrawArrays (GL_TRIANGLES, 0, (GLsizei) l->get_length());
    }

    std::cout << glGetError() << std::endl;
}

void ShadingObjectRenderer::add_light(std::shared_ptr<LightingSphere> light) {
    lights.push_back(light);
}
