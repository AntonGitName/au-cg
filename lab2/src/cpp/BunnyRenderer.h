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
#include "AbstractWindowListener.h"
#include "LoadedObject.h"
#include "ObjectBuffersWrapper.h"


class BunnyRenderer : public AbstractRenderer, public AbstractWindowListener {
public:
    BunnyRenderer();

    void render(GLFWwindow *window);

private:

    GLuint program_id;

    int width = 0;
    int height = 0;

    glm::mat3 transform;

    ObjectBuffersWrapper bunny;
public:
    void onMouseWheel(double xoffset, double yoffset) override;

    void onWindowSizeChanged(int width, int height) override;

    void onMouseButton(int button, int action, int mods) override;

    void onMousePos(double x, double y) override;

    void onKeyEvent(int key, int scancode, int action, int mods) override;

    GLint model_M;
    glm::mat4 model_mat;
};


#endif //AU_CG_SIMPLERENDERER_H
