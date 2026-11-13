#pragma once
#include <glad/gl.h>
#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"
#include "Texture.h"

class DrawableObject {
private:
    static GLuint nextID; // Čítač pro automatické generování unikátních ID
    GLuint id;            // Unikátní ID objektu (1 - 255)

    Model* model;
    ShaderProgram* shaderProgram;
    Transformation transformation;
    Texture* texture;

public:
    glm::vec3 color;

    DrawableObject(Model* model, ShaderProgram* shaderProgram, Texture* texture = nullptr);
    ~DrawableObject();

    GLuint getID() const { return id; }
    void setID(GLuint newID) { id = newID; }
    static void resetIDCounter() { nextID = 1; }

    void setTexture(Texture* tex);
    void draw();
    Transformation& getTransformation();
};