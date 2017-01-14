//
// Created by antonpp on 09.01.17.
//

#ifndef AU_CG_LIGHTINGSPHERE_H
#define AU_CG_LIGHTINGSPHERE_H

// local
#include "ObjectRenderer.h"

class LightingSphereRenderer : public ObjectRenderer {
public:
    LightingSphereRenderer(const std::shared_ptr<AbstractCamera> &camera_ptr);

private:
    void render_internal(GLFWwindow *window);

public:
    // movement
    glm::mat4 scale;
    glm::vec3 v0;
    glm::vec3 freq;
    glm::vec3 amplitude;
    glm::vec4 position;

    // light
    glm::vec4 color;
    glm::vec4 ka;
    glm::vec4 kd;
    glm::vec4 ks;
    GLfloat ns;

    void update_position();
    static void update_speed(bool increase);

private:
    float t = 0;

    static float dt;
    static constexpr float dt_scale = 0.9f;

    static std::shared_ptr<ObjectBuffersWrapper> get_g_sphere();
    static std::shared_ptr<ShaderWrapper> get_g_shader();

    static std::shared_ptr<ObjectBuffersWrapper> g_sphere;
    static std::shared_ptr<ShaderWrapper> g_shader;

    static void init();
};


#endif //AU_CG_LIGHTINGSPHERE_H