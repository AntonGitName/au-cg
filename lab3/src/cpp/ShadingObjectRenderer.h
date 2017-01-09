//
// Created by antonpp on 09.01.17.
//

#ifndef AU_CG_SHADINGOBJECTRENDERER_H
#define AU_CG_SHADINGOBJECTRENDERER_H


// local
#include "ObjectRenderer.h"
#include "LightingSphere.h"

class ShadingObjectRenderer : public ObjectRenderer {
public:
    ShadingObjectRenderer(std::shared_ptr<AbstractCamera> camera_ptr);

    void add_light(std::shared_ptr<LightingSphere>  light);
private:
    std::vector<std::shared_ptr<LightingSphere> > lights;

    glm::mat4 ModelView;

    void render_internal(GLFWwindow *window);

    void update_lights_info();
    void update_lights_position();
};


#endif //AU_CG_SHADINGOBJECTRENDERER_H
