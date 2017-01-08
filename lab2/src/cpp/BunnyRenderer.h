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

    ShaderWrapper bunny_shader;
    ShaderWrapper cube_shader;

    int width = 0;
    int height = 0;

    ObjectBuffersWrapper bunny;
    ObjectBuffersWrapper cube;

public:
    void onMouseWheel(double xoffset, double yoffset) override;

    void onWindowSizeChanged(int width, int height) override;

    void onMouseButton(int button, int action, int mods) override;

    void onMousePos(double x, double y) override;

    void onKeyEvent(int key, int scancode, int action, int mods) override;

    GLint view_cube_id;
    GLint model_cube_id;
    glm::mat4 model_cube;

    GLint view_bunny_id;
    GLint model_bunny_id;
    glm::mat4 model_bunny;

    glm::mat4 view;
};


#endif //AU_CG_SIMPLERENDERER_H
