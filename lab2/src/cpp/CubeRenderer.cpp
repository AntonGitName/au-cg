//
// Created by antonpp on 08.01.17.
//

#include <cstring>
#include "CubeRenderer.h"

CubeRenderer::CubeRenderer() : ObjectRenderer(ObjectBuffersWrapper(LoadedObject("obj/cube.obj"), true, false),
                                              ShaderWrapper({{"shaders/cube_vs.glsl", GL_VERTEX_SHADER},
                                                             {"shaders/cube_fs.glsl", GL_FRAGMENT_SHADER}})) {
    load_cubemap();
}

void CubeRenderer::load_cubemap() {
    static const char *faces[] = {"obj/cubemap/posx.jpg", "obj/cubemap/negx.jpg", "obj/cubemap/posy.jpg",
                                  "obj/cubemap/negy.jpg", "obj/cubemap/posz.jpg", "obj/cubemap/negz.jpg",};

//        static const char *faces[] = {"obj/darkskies/darkskies_rt.tga", "obj/darkskies/darkskies_lf.tga", "obj/darkskies/darkskies_ft.tga",
//                                  "obj/darkskies/darkskies_bk.tga", "obj/cubemap/darkskies_dn.tga", "obj/darkskies/darkskies_up.tga",};

//    cubemap_id = SOIL_load_OGL_cubemap(faces[0], faces[1], faces[2], faces[3], faces[4], faces[5], SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
//
//    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_id);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

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
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CubeRenderer::render(GLFWwindow *window) {
//    glUseProgram(shader.get_program());
//    glUniformMatrix4fv(model_id, 1, GL_FALSE, &model[0][0]);
//    glUniformMatrix4fv(view_id, 1, GL_FALSE, &view[0][0]);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_id);
//    glBindVertexArray(object.vao);
//    glDrawArrays(GL_TRIANGLES, 0, (GLsizei) object.length);

    ObjectRenderer::render(window);

//    std::cout << glGetError() << std::endl;
}

CubeRenderer::~CubeRenderer() {
    glDeleteTextures(1, &cubemap_id);
}
