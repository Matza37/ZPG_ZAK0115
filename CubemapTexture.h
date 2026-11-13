#pragma once
#include <glad/gl.h>
#include <vector>
#include <string>

class CubemapTexture {
private:
    GLuint textureID;

public:
    // Přebírá seznam 6 cest k souborům (posx, negx, posy, negy, posz, negz)
    CubemapTexture(const std::vector<std::string>& faces);
    ~CubemapTexture();

    void bind(GLuint slot = 0) const;
    GLuint getID() const { return textureID; }
};