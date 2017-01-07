//
// Created by antonpp on 06.01.17.
//

#include <iostream>
#include "Pane.h"

inline unsigned Pane::convertCoordinates(unsigned i, unsigned j) {
    return i * (VERTEX_NUMBER_Y + 1) + j;
}

Pane::Pane(float width, float height) : width(width), height(height) {
    float x0 = -width / 2;
    float y0 = -height / 2;
    float dx = width / VERTEX_NUMBER_X;
    float dy = height / VERTEX_NUMBER_Y;

    for (size_t i = 0; i <= VERTEX_NUMBER_X; ++i) {
        for (size_t j = 0; j <= VERTEX_NUMBER_Y; ++j) {
            glm::vec3 v;
            v.x = x0 + dx * i;
            v.y = y0 + dy * j;
            v.z = -1;
            vertices.push_back(v);
        }
    }

    for (unsigned i = 1; i <= VERTEX_NUMBER_X; ++i) {
        for (unsigned j = 0; j < VERTEX_NUMBER_Y; ++j) {
            indices.push_back(convertCoordinates(i - 1, j));
            indices.push_back(convertCoordinates(i, j));
            indices.push_back(convertCoordinates(i - 1, j + 1));
            indices.push_back(convertCoordinates(i, j));
            indices.push_back(convertCoordinates(i - 1, j + 1));
            indices.push_back(convertCoordinates(i, j + 1));
        }
    }


    glGenVertexArrays(1, &vertex_array);
    glGenBuffers(1, &vertex_buffer);
    glGenBuffers(1, &index_buffer);

    glBindVertexArray(vertex_array);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * indices.size(), indices.data(), GL_STATIC_DRAW);
    glEnable(GL_PRIMITIVE_RESTART);
    glPrimitiveRestartIndex((GLuint) vertices.size());
}

void Pane::draw() {
    glDrawElements(
            GL_TRIANGLES,                // mode
            (GLsizei) indices.size(),    // count
            GL_UNSIGNED_INT,             // type
            (void *) 0                   // element array buffer offset
    );
}

Pane::~Pane() {
    glDeleteBuffers(1, &vertex_buffer);
    glDeleteBuffers(1, &index_buffer);
    glDeleteVertexArrays(1, &vertex_array);
}

float Pane::get_height() {
    return height;
}

float Pane::get_width() {
    return width;
}
