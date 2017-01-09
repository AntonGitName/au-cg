//
// Created by antonpp on 06.01.17.
//

#ifndef AU_CG_SIMPLERENDERER_H
#define AU_CG_SIMPLERENDERER_H

// opengl
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

// std
#include <memory>

// local
#include "AbstractRenderer.h"
#include "ShaderWrapper.h"
#include "Pane.h"
#include "MandelbrotTexture.h"
#include "AbstractWindowListener.h"


class MandelbrotRenderer : public AbstractRenderer, public AbstractWindowListener {
public:
    MandelbrotRenderer(ShaderWrapper shaderWrapper);

    void render(GLFWwindow *window);

private:

    GLuint program_id;

    GLint mvp_id;
    GLint transform_id;
    GLint fractal_iterations_id;

    Pane pane;
    int fractal_iterations = 10;
    std::shared_ptr<MandelbrotTexture> custom_texture;

    int width = 0;
    int height = 0;
    float cursor_x = 0;
    float cursor_y = 0;
    bool isMousePressed = false;

    glm::mat4 transform;
    glm::mat4 view;
public:
    void onMouseWheel(double xoffset, double yoffset) override;

    void onWindowSizeChanged(int width, int height) override;

    void onMouseButton(int button, int action, int mods) override;

    void onMousePos(double x, double y) override;

    void onKeyEvent(int key, int scancode, int action, int mods) override;


};


#endif //AU_CG_SIMPLERENDERER_H