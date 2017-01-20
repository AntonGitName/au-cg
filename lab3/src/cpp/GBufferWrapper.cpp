//
// Created by antonpp on 19.01.17.
//

#include <iostream>
#include "GBufferWrapper.h"

namespace {
    void create_texture(size_t w, size_t h, GLuint *texture_id, GLint internal_format) {
        glGenTextures(1, texture_id);
        glBindTexture(GL_TEXTURE_2D, *texture_id);
        glTexImage2D(GL_TEXTURE_2D, 0, internal_format, (GLsizei) w, (GLsizei) h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
}

GBufferWrapper::GBufferWrapper(size_t w, size_t h) : width(w), height(h) {
    std::vector<GLenum> draw_buffers = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};

    glGenFramebuffers(1, &geometry_frame_buffer_id);

    create_texture(w, h, &position_texture_id, GL_RGB32F);
    create_texture(w, h, &normal_texture_id, GL_RGB16F);

    glBindFramebuffer(GL_FRAMEBUFFER, geometry_frame_buffer_id);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, position_texture_id, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, normal_texture_id, 0);

    glDrawBuffers((GLsizei) draw_buffers.size(), draw_buffers.data());


    glGenRenderbuffers(1, &render_buffer_id);
    glBindRenderbuffer(GL_RENDERBUFFER, render_buffer_id);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, (GLsizei) w, (GLsizei) h);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, render_buffer_id);

    if (glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw std::runtime_error("Could not create frame buffer");
    }

    glGenFramebuffers(1, &color_frame_buffer_id);

    create_texture(w, h, &color_texture_id, GL_RGB32F);
    glBindFramebuffer(GL_FRAMEBUFFER, color_frame_buffer_id);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_texture_id, 0);
    glDrawBuffers(1, draw_buffers.data());

    if (glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw std::runtime_error("Could not create frame buffer");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GBufferWrapper::~GBufferWrapper() {
    std::vector<GLuint> fbs = {geometry_frame_buffer_id, color_frame_buffer_id};
    std::vector<GLuint> textures = {position_texture_id, normal_texture_id, color_texture_id};
    glDeleteFramebuffers((GLsizei) fbs.size(), fbs.data());
    glDeleteTextures((GLsizei) textures.size(), textures.data());
    glDeleteRenderbuffers(1, &render_buffer_id);
}

void GBufferWrapper::bind_geometry_write() {
    glBindFramebuffer(GL_FRAMEBUFFER, geometry_frame_buffer_id);
}

void GBufferWrapper::bind_geometry_read() {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, geometry_frame_buffer_id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, position_texture_id);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, normal_texture_id);
    glBindFramebuffer(GL_FRAMEBUFFER, color_frame_buffer_id);
}

void GBufferWrapper::bind_color_read() {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, color_frame_buffer_id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, color_texture_id);
}

void GBufferWrapper::bind_color_write() {
    glBindFramebuffer(GL_FRAMEBUFFER, color_frame_buffer_id);
}

void GBufferWrapper::bind_default_write() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GBufferWrapper::blit_buffer() {
    glBlitFramebuffer(0, 0, (GLint) width, (GLint) height, 0, 0, (GLint) width, (GLint) height, GL_DEPTH_BUFFER_BIT,
                      GL_NEAREST);
}

void GBufferWrapper::bind_default_draw() {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}
