//
// Created by antonpp on 08.01.17.
//

#include <cstring>
#include "CubeRenderer.h"


CubeRenderer::CubeRenderer(std::shared_ptr<CameraCentered> camera_ptr)
        : ObjectRenderer(camera_ptr,
                         ObjectBuffersWrapper(LoadedObject("obj/cube.obj"), true, false),
                         ShaderWrapper({{"shaders/cube_vs.glsl", GL_VERTEX_SHADER},
                                        {"shaders/cube_fs.glsl", GL_FRAGMENT_SHADER}})) {
    load_cubemap();
}

void CubeRenderer::load_cubemap() {
    static const char *faces[] = {"obj/cubemap/posx.jpg", "obj/cubemap/negx.jpg", "obj/cubemap/posy.jpg",
                                  "obj/cubemap/negy.jpg", "obj/cubemap/posz.jpg", "obj/cubemap/negz.jpg",};

    glGenTextures(1, &cubemap_id);

    int width, height;
    unsigned char *image;
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_id);
    for (GLuint i = 0; i < 6; i++) {
        image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
        if (!image) {
            throw std::runtime_error("Could not load cubemap image: " + std::string(faces[i]));
        }
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        SOIL_free_image_data(image);
    }

    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CubeRenderer::render(GLFWwindow *window) {

    glDepthMask(GL_FALSE);
    glDisable(GL_DEPTH_TEST);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_id);

    ObjectRenderer::render(window);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
}

CubeRenderer::~CubeRenderer() {
    glDeleteTextures(1, &cubemap_id);
}
