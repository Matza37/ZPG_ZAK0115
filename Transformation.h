#pragma once
#include <glm/glm.hpp>

class ShaderProgram; // Forward declaration

class Transformation {
private:
    glm::vec3 translation = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f);
    float rotationX = 0.0f;
    float rotationY = 0.0f;
    float rotationZ = 0.0f;

    bool useManualMatrix = false;
    glm::mat4 manualMatrix = glm::mat4(1.0f);

public:
    Transformation();

    // Pozice a měřítko
    void setPosition(const glm::vec3& pos);
    void setScale(const glm::vec3& scl);
    glm::vec3 getPosition() const { return translation; }
    glm::vec3 getScale() const { return scale; }

    // Rotace
    void setRotationX(float rotX);
    void setRotationY(float rotY);
    void setRotationZ(float rotZ);
    void setRotation(float rotX, float rotY, float rotZ);
    void setRotation(const glm::vec3& rot);
    void setRotation(float angleInRadians, const glm::vec3& axis);
    void rotate(float angleInRadians, const glm::vec3& axis);

    float getRotationX() const;
    float getRotationY() const;
    float getRotationZ() const;

    // Přímá práce s maticí
    void setMatrix(const glm::mat4& m) {
        manualMatrix = m;
        useManualMatrix = true;
    }
    glm::mat4 getModelMatrix() const;

    void applyToShader(ShaderProgram* shaderProgram);
};