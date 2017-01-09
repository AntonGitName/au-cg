//
// Created by antonpp on 09.01.17.
//

#ifndef AU_CG_LIGHTINGSPHERE_H
#define AU_CG_LIGHTINGSPHERE_H

// local
#include "ObjectRenderer.h"

class LightingSphere : public ObjectRenderer {
public:
    LightingSphere(const std::shared_ptr<AbstractCamera> &camera_ptr);

    void render(GLFWwindow *window);

    GLuint get_vao() const;

public:
    glm::mat4 scale;
    glm::vec3 color;
    glm::vec3 v0;
    glm::vec3 freq;
    glm::vec3 amplitude;
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 position;

    float t;

    void update_position();

    static constexpr float dt = 0.05f;

    size_t get_length() const;

private:
    static std::shared_ptr<ObjectBuffersWrapper> get_g_sphere();
    static std::shared_ptr<ShaderWrapper> get_g_shader();

    static std::shared_ptr<ObjectBuffersWrapper> g_sphere;
    static std::shared_ptr<ShaderWrapper> g_shader;

    static void init();
};


#endif //AU_CG_LIGHTINGSPHERE_H
