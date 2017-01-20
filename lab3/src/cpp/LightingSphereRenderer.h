//
// Created by antonpp on 09.01.17.
//

#ifndef AU_CG_LIGHTINGSPHERE_H
#define AU_CG_LIGHTINGSPHERE_H

// local
#include "ObjectRenderer.h"
#include "PointLightInfo.h"
#include "WindowWrapper.h"

class LightingSphereRenderer : public ObjectRenderer {
public:
    LightingSphereRenderer(const std::shared_ptr<AbstractCamera> &camera_ptr);

private:
    void setup_render(GLFWwindow *window);

public:
    glm::mat4 scale;
    glm::vec3 v0;
    glm::vec3 freq;
    glm::vec3 amplitude;
    glm::vec4 position;

    std::shared_ptr<PointLightInfo> light_info_ptr;

    void update_position();

private:
    float t = 0;

    static std::shared_ptr<ObjectBuffersWrapper> get_g_sphere();
    static std::shared_ptr<ShaderWrapper> get_g_shader();

    static std::shared_ptr<ObjectBuffersWrapper> g_sphere;
    static std::shared_ptr<ShaderWrapper> g_shader;

    static void init();
};


#endif //AU_CG_LIGHTINGSPHERE_H
