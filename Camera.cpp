#include "Camera.h"
#include "ShaderProgram.h"
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

Camera::Camera(ShaderProgram* shaderProgram)
    : m_shaderProgram(shaderProgram),
    eye(0.0f, 1.0f, 5.0f),
    up(0.0f, 1.0f, 0.0f),
    alpha(glm::radians(90.0f)),
    fi(glm::radians(-90.0f)),
    fov(45.0f), // Výchozí FOV
    sensitivity(0.003f),
    speed(5.0f),
    firstMouse(true),
    lastX(0.0), lastY(0.0)
{
    target.x = sin(alpha) * cos(fi);
    target.z = sin(alpha) * sin(fi);
    target.y = cos(alpha);
}

Camera::~Camera() {}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(eye, eye + target, up);
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio) const {
    return glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 100.0f);
}

void Camera::setFov(float newFov) {
    fov = newFov;
}

void Camera::updateMatrices(ShaderProgram* targetShader) {
    if (targetShader != nullptr) {
        // Zjištění reálných rozměrů okna z GLFW
        GLFWwindow* window = glfwGetCurrentContext();
        int width = 800, height = 600;
        if (window) {
            glfwGetFramebufferSize(window, &width, &height);
        }
        if (height == 0) height = 1;
        float aspectRatio = static_cast<float>(width) / static_cast<float>(height);

        targetShader->use();
        targetShader->setViewMatrix(getViewMatrix());
        targetShader->setProjectionMatrix(getProjectionMatrix(aspectRatio));
    }
}

void Camera::processKeyboard(float dt) {
    GLFWwindow* window = glfwGetCurrentContext();
    if (!window) return;

    glm::vec3 right = glm::normalize(glm::cross(target, up));

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        eye += target * speed * dt;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        eye -= target * speed * dt;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        eye -= right * speed * dt;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        eye += right * speed * dt;
}

void Camera::processMouse() {
    GLFWwindow* window = glfwGetCurrentContext();
    if (!window) return;

    // Check if Right Mouse Button is pressed
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        if (firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = static_cast<float>(xpos - lastX);
        float yoffset = static_cast<float>(lastY - ypos); // Reversed Y

        lastX = xpos;
        lastY = ypos;

        xoffset *= sensitivity;
        yoffset *= sensitivity;

        fi += xoffset;
        alpha -= yoffset;

        // Constrain pitch to avoid flipping
        alpha = std::clamp(alpha, 0.01f, 3.14f - 0.01f);

        // Recalculate target vector
        target.x = sin(alpha) * cos(fi);
        target.z = sin(alpha) * sin(fi);
        target.y = cos(alpha);
        target = glm::normalize(target);
    }
    else {
        firstMouse = true;
    }
}

void Camera::setPosition(const glm::vec3& pos) { eye = pos; }
glm::vec3 Camera::getPosition() const { return eye; }