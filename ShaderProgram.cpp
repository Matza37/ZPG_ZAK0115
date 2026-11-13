#include "ShaderProgram.h"
#include "Camera.h"
#include <iostream>
#include <cstdlib>

ShaderProgram::ShaderProgram(Shader* vertexShader, Shader* fragmentShader)
    : id(0), m_camera(nullptr) {
    id = glCreateProgram();

    if (id == 0) {
        std::cerr << "CRITICAL ERROR: Failed to create shader program object!" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    glAttachShader(id, vertexShader->getID());
    glAttachShader(id, fragmentShader->getID());
    glLinkProgram(id);

    // Check for linking errors
    GLint success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetProgramInfoLog(id, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "CRITICAL ERROR: Shader Program linking failed:\n" << infoLog << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(id);
}

void ShaderProgram::use() {
    glUseProgram(id);
}

void ShaderProgram::unuse() {
    glUseProgram(0);
}

void ShaderProgram::setCamera(Camera* camera) {
    m_camera = camera;
}

Camera* ShaderProgram::getCamera() const {
    return m_camera;
}

void ShaderProgram::setUniform(const std::string& name, float value) {
    glUseProgram(id); // Ensure program is active before getting location
    GLint location = glGetUniformLocation(id, name.c_str());
    if (location == -1) {
        std::cerr << "Warning: Uniform '" << name << "' doesn't exist in program ID " << id << "!" << std::endl;
    }
    else {
        glUniform1f(location, value);
    }
}

void ShaderProgram::setUniform(const std::string& name, int value) {
    glUseProgram(id);
    GLint location = glGetUniformLocation(id, name.c_str());
    if (location == -1) {
        std::cerr << "Warning: Uniform '" << name << "' doesn't exist in program ID " << id << "!" << std::endl;
    }
    else {
        glUniform1i(location, value); // Nastavení integer uniformy pro textury
    }
}

void ShaderProgram::setUniform(const std::string& name, const glm::vec3& value) {
    glUseProgram(id); // Ensure program is active before getting location
    GLint location = glGetUniformLocation(id, name.c_str());
    if (location == -1) {
        std::cerr << "Warning: Uniform '" << name << "' doesn't exist in program ID " << id << "!" << std::endl;
    }
    else {
        glUniform3f(location, value.x, value.y, value.z);
    }
}

void ShaderProgram::setUniform(const std::string& name, const glm::vec4& value) {
    glUseProgram(id); // Ensure program is active before getting location
    GLint location = glGetUniformLocation(id, name.c_str());
    if (location == -1) {
        std::cerr << "Warning: Uniform '" << name << "' doesn't exist in program ID " << id << "!" << std::endl;
    }
    else {
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }
}

void ShaderProgram::setUniform(const std::string& name, const glm::mat4& matrix) {
    glUseProgram(id);
    GLint location = glGetUniformLocation(id, name.c_str());
    if (location == -1) {
        std::cout << "Warning: Uniform '" << name << "' doesn't exist in program ID " << id << "!\n";
    }
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::setViewMatrix(const glm::mat4& view) {
    glUseProgram(id);
    GLint location = glGetUniformLocation(id, "viewMatrix");
    if (location != -1) {
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(view));
    }
}

void ShaderProgram::setProjectionMatrix(const glm::mat4& projection) {
    glUseProgram(id);
    GLint location = glGetUniformLocation(id, "projectMatrix");
    if (location != -1) {
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projection));
    }
}