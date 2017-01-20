//
// Created by antonpp on 09.01.17.
//

#include "ShadingObjectRenderer.h"

using std::make_shared;

ShadingObjectRenderer::ShadingObjectRenderer(std::shared_ptr<AbstractCamera> camera_ptr)
        : ObjectRenderer(camera_ptr, nullptr,
                         make_shared<ObjectBuffersWrapper>(LoadedObject("obj/suzanne.obj"), true, false)),
          geometry_shader(ShaderWrapper::create("geometry_vs.glsl", "geometry_fs.glsl")),
          light_shader(ShaderWrapper::create("light_vs.glsl", "light_fs.glsl")),
          blend_framebuffers_shader(ShaderWrapper::create("post_vs.glsl", "post_fs.glsl"))
        , screen_square({{-1.0, -1.0, 0},
                         {1.0,  -1.0, 0},
                         {1.0,  1.0,  0},
                         {1.0,  1.0,  0},
                         {-1.0, 1.0,  0},
                         {-1.0, -1.0, 0}}) {
    shader_ptr = geometry_shader;
    model = glm::scale(glm::vec3(0.5, 0.5, 0.5));
    onWindowSizeChanged(1024, 768);
    glUseProgram(light_shader->get_program());
    glUniform1f(get_uniform("gamma"), 1);
}

void ShadingObjectRenderer::add_light(std::shared_ptr<PointLightInfo> light) {
    lights.insert(light);
    update_lights_info();
}

void ShadingObjectRenderer::render_internal(GLFWwindow *window) {
//    model = glm::rotate(model, 0.03f, glm::vec3(0, 0, 1));
    int i = 0;
    update_lights_position();
    std::cout << ++i << ": " << glGetError() << std::endl;

    buffer_ptr->bind_geometry_write();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    std::cout << ++i << ": " << glGetError() << std::endl;

    shader_ptr = geometry_shader;
    ObjectRenderer::render_internal(window);
    std::cout << ++i << ": " << glGetError() << std::endl;

    buffer_ptr->bind_geometry_read();
    buffer_ptr->bind_color_write();
    std::cout << ++i << ": " << glGetError() << std::endl;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader_ptr = light_shader;
    ObjectRenderer::render_internal(window);
    std::cout << ++i << ": " << glGetError() << std::endl;

    buffer_ptr->bind_default_write();
    glActiveTexture (GL_TEXTURE0);
    glBindTexture (GL_TEXTURE_2D, buffer_ptr->color_texture_id);
    // draw the quad that covers the screen area
    glDrawArrays (GL_TRIANGLES, 0, 6);

//    buffer_ptr->bind_default_write();
//    buffer_ptr->bind_geometry_read();
//    buffer_ptr->bind_default_draw();
//    buffer_ptr->blit_buffer();
//    buffer_ptr->bind_color_read();
//    glBlitNamedFramebuffer(buffer_ptr->color_frame_buffer_id, 0, 0, 0, 1024, 768, 0, 0, 1024, 768, GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT, GL_NEAREST);
//    glBlitFramebuffer(0, 0, 1024, 768, 0, 0, 1024, 768, GL_COLOR_BUFFER_BIT, GL_NEAREST);

//    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
//
    std::cout << ++i << ": " << glGetError() << std::endl;
}

template<class T>
void f(T v) {
    std::cout << v.x << " " << v.y << " " << v.z << std::endl;
}

void ShadingObjectRenderer::update_lights_position() {
    std::vector<glm::vec3> positions;
    for (auto light : lights) {
        positions.push_back(light->position);
    }

    glUseProgram(light_shader->get_program());
    glUniform3fv(get_uniform("light_position"), (GLsizei) positions.size(), (const GLfloat *) positions.data());
}

void ShadingObjectRenderer::update_lights_info() {
    glUseProgram(light_shader->get_program());
    GLint num = (GLint) lights.size();
    glUniform1i(get_uniform("lights_num"), num);
    std::vector<glm::vec3> info;

    for (auto light : lights) {
        info.push_back(light->specular_color);
    }
    glUniform3fv(get_uniform("specular_color"), num, (const GLfloat *) info.data());

    info.clear();
    for (auto light : lights) {
        info.push_back(light->specular_coef);
    }
    glUniform4fv(get_uniform("specular_coef"), num, (const GLfloat *) info.data());

    info.clear();
    for (auto light : lights) {
        info.push_back(light->diffuse_color);
    }
    glUniform4fv(get_uniform("diffuse_color"), num, (const GLfloat *) info.data());

    info.clear();
    for (auto light : lights) {
        info.push_back(light->diffuse_coef);
    }
    glUniform4fv(get_uniform("diffuse_coef"), num, (const GLfloat *) info.data());

    std::vector<GLfloat> ns;
    for (auto light : lights) {
        ns.push_back(light->specular_exponent);
    }
    glUniform1fv(get_uniform("specular_exponent"), num, ns.data());
}

void ShadingObjectRenderer::remove_light(std::shared_ptr<PointLightInfo> light) {
    lights.erase(light);
    update_lights_info();
}

void ShadingObjectRenderer::onWindowSizeChanged(int width, int height) {
    buffer_ptr = make_shared<GBufferWrapper>(width, height);

    glUseProgram(light_shader->get_program());
    glUniform1i(get_uniform("screen_width"), width);
    glUniform1i(get_uniform("screen_height"), height);
}

void ShadingObjectRenderer::setShader(std::shared_ptr<ShaderWrapper> shader) {
    shader_ptr = shader;
}
