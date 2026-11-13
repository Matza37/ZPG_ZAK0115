#pragma once
#include <glad/gl.h>

class Model {
private:
    GLuint vao;
    GLuint vbo;
    int vertexCount;

public:
    Model(const float* vertices, int size, int floatsPerVertex = 6);
    ~Model();

    void draw();
};