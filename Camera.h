#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class ShaderProgram;

class Camera {
private:
    ShaderProgram* m_shaderProgram;

    glm::vec3 eye;
    glm::vec3 target;
    glm::vec3 up;

    float alpha;
    float fi;
    float fov; // Přidáno pro zorný úhel

    float sensitivity;
    float speed;

    bool firstMouse;
    double lastX, lastY;

public:
    Camera(ShaderProgram* shaderProgram);
    ~Camera();

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix(float aspectRatio) const;
    void updateMatrices(ShaderProgram* targetShader);

    void processKeyboard(float dt);
    void processMouse();

    void setPosition(const glm::vec3& pos);
    glm::vec3 getPosition() const;

    void setFov(float newFov); // Přidán setter pro FOV
};