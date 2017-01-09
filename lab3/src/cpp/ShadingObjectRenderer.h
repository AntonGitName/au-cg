//
// Created by antonpp on 09.01.17.
//

#ifndef AU_CG_SHADINGOBJECTRENDERER_H
#define AU_CG_SHADINGOBJECTRENDERER_H


// local
#include "ObjectRenderer.h"
#include "gbuffer.h"
#include "LightingSphere.h"

class ShadingObjectRenderer : public AbstractRenderer {
public:
    ShadingObjectRenderer(std::shared_ptr<AbstractCamera> camera_ptr);

    void render(GLFWwindow *window);

    void add_light(std::shared_ptr<LightingSphere>  light);
private:
    std::vector<std::shared_ptr<LightingSphere> > lights;

    GBuffer gb;
    std::shared_ptr<ShaderWrapper> geometry_pass;
    std::shared_ptr<ShaderWrapper> light_pass;

    GLint gpass_M_loc;
    GLint gpass_V_loc;
    GLint gpass_P_loc;

    GLint lpass_P_loc = -1;
    GLint lpass_V_loc = -1;
    GLint lpass_M_loc = -1;
    GLint lpass_L_p_loc = -1;
    GLint lpass_L_d_loc = -1;
    GLint lpass_L_s_loc = -1;
    GLint lpass_p_tex_loc = -1;
    GLint lpass_n_tex_loc = -1;

    GLint proj_id;
    GLint view_id;
    GLint modl_id;
    std::shared_ptr<AbstractCamera> camera_ptr;
    glm::mat4 model;

    std::shared_ptr<ObjectBuffersWrapper> object_ptr;

};


#endif //AU_CG_SHADINGOBJECTRENDERER_H
