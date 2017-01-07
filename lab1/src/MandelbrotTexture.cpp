//
// Created by antonpp on 06.01.17.
//

#include "MandelbrotTexture.h"

GLuint MandelbrotTexture::get_texture_id() const {
    return texture_id;
}

MandelbrotTexture::~MandelbrotTexture() {
    glDeleteTextures(1, &texture_id);
}

MandelbrotTexture::MandelbrotTexture(int fractal_iterations) : texture_id(0) {
    std::vector<GLfloat> colors;
    const GLfloat dc = 1.0f / (fractal_iterations + 1);
    for (int i = 0; i < fractal_iterations; i++) {
        const auto x = (dc * i);
        colors.push_back(x);
        colors.push_back((GLfloat) sin(x * M_PI_2));
        colors.push_back(1 - x);
    }
    colors.push_back(0);
    colors.push_back(0);
    colors.push_back(0);


    GLuint color_buffer;
    glGenBuffers(1, &color_buffer);
    glBindBuffer(GL_TEXTURE_BUFFER, color_buffer);
    glBufferData(GL_TEXTURE_BUFFER, sizeof(GLfloat) * colors.size(), 0, GL_STATIC_DRAW);
    glBufferSubData(GL_TEXTURE_BUFFER, 0, sizeof(GLfloat) * colors.size(), colors.data());

    glGenTextures(1, &texture_id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_BUFFER, texture_id);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RGB32F, color_buffer);
}
