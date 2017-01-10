//
// Created by Anton Mordberg on 10/01/2017.
//

#ifndef AU_CG_IMAGERENDERER_H
#define AU_CG_IMAGERENDERER_H

// opengl
#include <SOIL/SOIL.h>

// local
#include "ObjectRenderer.h"

class ImageRenderer : public ObjectRenderer {

public:
    ImageRenderer(const std::shared_ptr<AbstractCamera> &camera_ptr);

    void render_internal(GLFWwindow *window);
private:

    GLuint texture_id;


    static std::shared_ptr<ObjectBuffersWrapper> get_g_pane();
    static std::shared_ptr<ShaderWrapper> get_g_shader();

    static std::shared_ptr<ObjectBuffersWrapper> g_pane;
    static std::shared_ptr<ShaderWrapper> g_shader;

    static void init();
};


#endif //AU_CG_IMAGERENDERER_H
