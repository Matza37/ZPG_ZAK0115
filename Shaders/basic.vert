#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectMatrix;

out vec3 vertexColor;

void main() {
    // Correct transformation pipeline: Projection * View * Model * Position
    gl_Position = projectMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
}