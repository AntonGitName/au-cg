//
// Created by antonpp on 06.01.17.
//

#include "ShaderWrapper.h"

ShaderWrapper::ShaderWrapper(const std::vector<std::pair<std::string, GLenum>> paths) {

    std::vector<GLuint> shader_ids;

    for (auto pathType : paths) {
        auto shader_id = glCreateShader(pathType.second);

        std::ifstream input(pathType.first);

        if (!input) {
            throw std::runtime_error("Could not find shader file: " + pathType.first);
        }

        std::string shaderCode = std::string(std::istreambuf_iterator<char>(input),
                                             std::istreambuf_iterator<char>());

        const char* c_str = shaderCode.c_str();
        glShaderSource(shader_id, 1, &c_str, NULL);
        glCompileShader(shader_id);

        // check
        GLint compilation_result = GL_FALSE;
        GLint log_length;
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compilation_result);
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);
        if ( log_length > 0 ){
            std::string shader_error_message((unsigned long) (log_length + 1), ' ');
            glGetShaderInfoLog(shader_id, log_length, NULL, &shader_error_message[0]);
            throw std::runtime_error("Could not compile shader: " + pathType.first + "\n" + shader_error_message);
        }

        shader_ids.push_back(shader_id);
    }

    program_id = glCreateProgram();

    for (auto shader_id : shader_ids) {
        glAttachShader(program_id, shader_id);
    }

    glLinkProgram(program_id);

    for (auto shader_id : shader_ids) {
        glDetachShader(program_id, shader_id);
        glDeleteShader(shader_id);
    }
}

GLuint ShaderWrapper::get_program() const {
    return program_id;
}

ShaderWrapper::~ShaderWrapper() {
    glDeleteProgram(program_id);
}