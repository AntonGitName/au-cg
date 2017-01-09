//
// Created by antonpp on 06.01.17.
//

#ifndef AU_CG_SHADERWRAPPER_H
#define AU_CG_SHADERWRAPPER_H

// opengl
#include <GL/glew.h>

// std
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>

class ShaderWrapper {
public:
    ShaderWrapper(const ShaderWrapper&) = delete;
    ShaderWrapper(const std::vector<std::pair<std::string, GLenum>> paths);
    ~ShaderWrapper();

    GLuint get_program() const;

private:
    GLuint program_id;
};


#endif //AU_CG_SHADERWRAPPER_H
