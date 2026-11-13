#include "DrawableObject.h"

GLuint DrawableObject::nextID = 1;

DrawableObject::DrawableObject(Model* model, ShaderProgram* shaderProgram, Texture* texture)
    : model(model), shaderProgram(shaderProgram), texture(texture), color(1.0f, 1.0f, 1.0f) {
    id = nextID++;
    if (nextID > 255) {
        nextID = 1; // Ochrana proti přetečení 8bitového stencil bufferu
    }
}

DrawableObject::~DrawableObject() {}

void DrawableObject::setTexture(Texture* tex) {
    texture = tex;
}

void DrawableObject::draw() {
    shaderProgram->use();
    shaderProgram->setUniform("fragmentColor", color);

    if (texture != nullptr) {
        texture->bind(0);
        shaderProgram->setUniform("texture1", 0);
    }

    transformation.applyToShader(shaderProgram);
    model->draw();
    shaderProgram->unuse();
}

Transformation& DrawableObject::getTransformation() {
    return transformation;
}