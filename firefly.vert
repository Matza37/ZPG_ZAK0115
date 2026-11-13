#version 460 core
layout(location = 0) in vec3 aPos;

uniform mat4 modelMatrix = mat4(1.0);
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectMatrix = mat4(1.0);

void main() {
    gl_Position = projectMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
}