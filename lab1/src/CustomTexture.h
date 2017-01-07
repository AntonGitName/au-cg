//
// Created by antonpp on 06.01.17.
//

#ifndef AU_CG_CUSTOMTEXTURE_H
#define AU_CG_CUSTOMTEXTURE_H

// opengl
#include <GL/glew.h>

// std
#include <cmath>
#include <vector>

class CustomTexture {
public:
    CustomTexture(int fractal_iterations);
    ~CustomTexture();
    GLuint get_texture_id() const;
private:
    GLuint texture_id;
};


#endif //AU_CG_CUSTOMTEXTURE_H
