//
// Created by antonpp on 13.01.17.
//

#ifndef AU_CG_AXISRENDERER_H
#define AU_CG_AXISRENDERER_H

// opengl
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/vec2.hpp>
#include <GL/glew.h>

// std
#include <vector>

// local
#include "AbstractRenderer.h"
#include "AbstractShaderRenderer.h"

class AxisRenderer : public AbstractShaderRenderer {
public:
    AxisRenderer(std::shared_ptr<AbstractCamera> camera_ptr);
    ~AxisRenderer();
    void render(GLFWwindow *window);

private:
    GLuint vao;
    GLuint v_vbo;
    GLuint c_vbo;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> colors;


    static std::shared_ptr<ShaderWrapper> g_shader;
    static std::shared_ptr<ShaderWrapper> get_g_shader();
    static void init();
};


#endif //AU_CG_AXISRENDERER_H
