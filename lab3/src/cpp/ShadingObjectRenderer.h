//
// Created by antonpp on 09.01.17.
//

#ifndef AU_CG_SHADINGOBJECTRENDERER_H
#define AU_CG_SHADINGOBJECTRENDERER_H


// std
#include <set>

// local
#include "ObjectRenderer.h"
#include "LightingSphereRenderer.h"
#include "GBufferWrapper.h"

class ShadingObjectRenderer : public ObjectRenderer, public AbstractWindowListener {
public:
    ShadingObjectRenderer(std::shared_ptr<AbstractCamera> camera_ptr);

    void add_light(std::shared_ptr<PointLightInfo>  light);
    void remove_light(std::shared_ptr<PointLightInfo>  light);
    void onWindowSizeChanged(int width, int height);

private:
    std::set<std::shared_ptr<PointLightInfo> > lights;

    void render_internal(GLFWwindow *window);

    void update_lights_info();
    void update_lights_position();

    std::shared_ptr<GBufferWrapper> buffer_ptr;

    std::shared_ptr<ShaderWrapper> geometry_shader;
    std::shared_ptr<ShaderWrapper> light_shader;
    std::shared_ptr<ShaderWrapper> blend_framebuffers_shader;

    ObjectBuffersWrapper screen_square;

    void setShader(std::shared_ptr<ShaderWrapper> shader);
};


#endif //AU_CG_SHADINGOBJECTRENDERER_H
