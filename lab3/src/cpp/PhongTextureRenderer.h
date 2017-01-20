//
// Created by antonpp on 20.01.17.
//

#ifndef AU_CG_PHONGTEXTURERENDERER_H
#define AU_CG_PHONGTEXTURERENDERER_H


// local
#include "ImageRenderer.h"
#include "PhongRenderer.h"

class PhongTextureRenderer : public PhongRenderer, public ImageRenderer{
public:
    PhongTextureRenderer(const std::shared_ptr<AbstractCamera> &camera_ptr);

private:
    void setup_render(GLFWwindow *window);
};


#endif //AU_CG_PHONGTEXTURERENDERER_H
