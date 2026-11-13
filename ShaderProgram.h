#pragma once
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <string>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

// Forward declaration for cross-reference
class Camera;

class ShaderProgram {
private:
    GLuint id;
    Camera* m_camera; // Cross-reference to Camera

public:
    ShaderProgram(Shader* vertexShader, Shader* fragmentShader);
    ~ShaderProgram();

    void use();
    void unuse();

    void setCamera(Camera* camera);
    Camera* getCamera() const;

    void setUniform(const std::string& name, float value);
    void setUniform(const std::string& name, int value);
    void setUniform(const std::string& name, const glm::vec3& value);
    void setUniform(const std::string& name, const glm::vec4& value);
    void setUniform(const std::string& name, const glm::mat4& matrix);

    void setViewMatrix(const glm::mat4& view);
    void setProjectionMatrix(const glm::mat4& projection);
};