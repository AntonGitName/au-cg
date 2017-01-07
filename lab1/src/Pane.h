//
// Created by antonpp on 06.01.17.
//

#ifndef AU_CG_PANE_H
#define AU_CG_PANE_H

// opengl
#include <GL/glew.h>
#include <glm/vec3.hpp>

// std
#include <vector>

class Pane {
public:
    Pane(float width, float height);
    ~Pane();
    void draw();

    float get_height();

    float get_width();

private:
    GLuint vertex_buffer;
    GLuint index_buffer;
    GLuint vertex_array;

    float width;
    float height;

    const static int VERTEX_NUMBER_X = 1024;
    const static int VERTEX_NUMBER_Y = 768;

    std::vector<glm::vec3> vertices;
    std::vector<unsigned > indices;

    unsigned int convertCoordinates(unsigned int i, unsigned int j);
};


#endif //AU_CG_PANE_H
