//
// Created by antonpp on 19.01.17.
//

#ifndef AU_CG_GBUFFERWRAPPER_H
#define AU_CG_GBUFFERWRAPPER_H


// opengl
#include <GL/glew.h>

// std
#include <vector>
#include <stdexcept>


class GBufferWrapper {
public:
    GBufferWrapper(size_t w, size_t h);
    ~GBufferWrapper();

    void bind_geometry_write();
    void bind_geometry_read();
    void bind_color_read();
    void bind_color_write();
    void bind_default_write();
    void bind_default_draw();
    void blit_buffer();


public:
    size_t width;
    size_t height;

    GLuint geometry_frame_buffer_id;
    GLuint color_frame_buffer_id;
    GLuint position_texture_id;
    GLuint normal_texture_id;
    GLuint color_texture_id;
    GLuint render_buffer_id;
};


#endif //AU_CG_GBUFFERWRAPPER_H
