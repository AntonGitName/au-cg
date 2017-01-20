//
// Created by antonpp on 20.01.17.
//

#ifndef AU_CG_PHONGRENDERER_H
#define AU_CG_PHONGRENDERER_H


// opengl
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// std
#include <memory>
#include <set>

// local
#include "PointLightInfo.h"
#include "AbstractShaderRenderer.h"

class PhongRenderer: public virtual AbstractShaderRenderer {
public:
    PhongRenderer(const std::shared_ptr<AbstractCamera> &camera_ptr,
                  const std::shared_ptr<ShaderWrapper> &shader_ptr);

    void add_light(std::shared_ptr<PointLightInfo>  light);
    void remove_light(std::shared_ptr<PointLightInfo>  light);

protected:
    void setup_render(GLFWwindow *window);

private:
    std::set<std::shared_ptr<PointLightInfo> > lights;

    void update_lights_info();
    void update_lights_position();
};


#endif //AU_CG_PHONGRENDERER_H
