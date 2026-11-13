#pragma once
#include <glad/gl.h>
#include <string>

class Texture {
private:
    GLuint textureID;

public:
    Texture(const char* filepath);
    ~Texture();

    void bind(GLuint slot = 0) const;
    GLuint getID() const { return textureID; }
};