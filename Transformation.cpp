#include "Transformation.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Transformation::Transformation()
    : translation(0.0f, 0.0f, 0.0f),
    scale(1.0f, 1.0f, 1.0f),
    rotationX(0.0f),
    rotationY(0.0f),
    rotationZ(0.0f),
    useManualMatrix(false),
    manualMatrix(1.0f) {}

void Transformation::setPosition(const glm::vec3& pos) { translation = pos; }
void Transformation::setScale(const glm::vec3& scl) { scale = scl; }

void Transformation::setRotationX(float rotX) { rotationX = rotX; useManualMatrix = false; }
void Transformation::setRotationY(float rotY) { rotationY = rotY; useManualMatrix = false; }
void Transformation::setRotationZ(float rotZ) { rotationZ = rotZ; useManualMatrix = false; }

void Transformation::setRotation(float rotX, float rotY, float rotZ) {
    rotationX = rotX;
    rotationY = rotY;
    rotationZ = rotZ;
    useManualMatrix = false;
}

void Transformation::setRotation(const glm::vec3& rot) {
    setRotation(rot.x, rot.y, rot.z);
}

void Transformation::setRotation(float angleInRadians, const glm::vec3& axis) {
    useManualMatrix = false;
    if (axis == glm::vec3(1.0f, 0.0f, 0.0f)) {
        rotationX = angleInRadians;
    }
    else if (axis == glm::vec3(0.0f, 1.0f, 0.0f)) {
        rotationY = angleInRadians;
    }
    else if (axis == glm::vec3(0.0f, 0.0f, 1.0f)) {
        rotationZ = angleInRadians;
    }
    else {
        // Pokud jde o obecnou osu rotace, spočte se matice přímo
        glm::mat4 M = glm::mat4(1.0f);
        M = glm::translate(M, translation);
        M = glm::rotate(M, angleInRadians, axis);
        M = glm::scale(M, scale);
        setMatrix(M);
    }
}

void Transformation::rotate(float angleInRadians, const glm::vec3& axis) {
    useManualMatrix = false;
    if (axis.x > 0.5f) rotationX += angleInRadians;
    if (axis.y > 0.5f) rotationY += angleInRadians;
    if (axis.z > 0.5f) rotationZ += angleInRadians;
}

float Transformation::getRotationX() const { return rotationX; }
float Transformation::getRotationY() const { return rotationY; }
float Transformation::getRotationZ() const { return rotationZ; }

glm::mat4 Transformation::getModelMatrix() const {
    if (useManualMatrix) {
        return manualMatrix;
    }
    glm::mat4 M = glm::mat4(1.0f);
    M = glm::translate(M, translation);
    M = glm::rotate(M, rotationX, glm::vec3(1.0f, 0.0f, 0.0f));
    M = glm::rotate(M, rotationY, glm::vec3(0.0f, 1.0f, 0.0f));
    M = glm::rotate(M, rotationZ, glm::vec3(0.0f, 0.0f, 1.0f));
    M = glm::scale(M, scale);
    return M;
}

void Transformation::applyToShader(ShaderProgram* shaderProgram) {
    // 1. Model Matrix
    shaderProgram->setUniform("modelMatrix", getModelMatrix());

    // 2. Update View and Projection on THIS specific shader program
    if (shaderProgram->getCamera() != nullptr) {
        shaderProgram->getCamera()->updateMatrices(shaderProgram);
    }
}