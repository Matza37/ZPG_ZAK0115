#include "Shader.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

Shader::Shader(GLenum shaderType, const char* sourceFile) {
    shaderID = glCreateShader(shaderType);

    std::ifstream file(sourceFile);
    if (!file.is_open()) {
        std::cerr << "CRITICAL ERROR: Unable to open shader file: " << sourceFile << std::endl;
        std::exit(EXIT_FAILURE); // Forces the app to stop when the path is wrong!
    }

    std::string shaderCode((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    const char* source = shaderCode.c_str();

    glShaderSource(shaderID, 1, &source, nullptr);
    glCompileShader(shaderID);

    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetShaderInfoLog(shaderID, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "Shader compilation failed in " << sourceFile << ":\n" << infoLog << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

Shader::~Shader() {
    glDeleteShader(shaderID);
}

GLuint Shader::getID() const {
    return shaderID;
}