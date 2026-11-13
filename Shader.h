#pragma once
#include <glad/gl.h>
#include <string>

class Shader {
private:
    GLuint shaderID;
public:
    Shader(GLenum shaderType, const char* sourceFile);
    ~Shader();
    GLuint getID() const;
};