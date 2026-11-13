#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord; // 3. atribut: UV souřadnice

out vec2 TexCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectMatrix;

void main() {
    gl_Position = projectMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
    TexCoord = aTexCoord; // Předání UV do fragment shaderu
}