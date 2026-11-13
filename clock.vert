#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec3 aColor;

uniform mat4 projectMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

uniform float uHourAngle;
uniform float uMinAngle;
uniform float uSecAngle;

out vec3 FragColor;
out vec3 FragNormal;

mat4 rotationZ(float angle) {
    float c = cos(angle);
    float s = sin(angle);
    return mat4(
        c,  s, 0.0, 0.0,
       -s,  c, 0.0, 0.0,
      0.0, 0.0, 1.0, 0.0,
      0.0, 0.0, 0.0, 1.0
    );
}

void main() {
    vec4 pos = vec4(aPosition, 1.0);
    vec3 color = aColor;

// Prohození úhlů podle toho, která ručička je která
    if (color.r > 0.5 && color.g < 0.2 && color.b < 0.2) {
        // Pokud je tato barva hodinová ručička, dejte sem uSecAngle (nebo opačně podle toho, jak to potřebujete)
        mat4 rot = rotationZ(uSecAngle); 
        pos = rot * pos;
    } 
    else if (color.g > 0.5 && color.r < 0.2 && color.b < 0.2) {
        // Minutová ručička
        mat4 rot = rotationZ(uMinAngle);
        pos = rot * pos;
    } 
    else if (color.b > 0.5 && color.r < 0.2 && color.g < 0.2) {
        // Hodinová ručička
        mat4 rot = rotationZ(uHourAngle);
        pos = rot * pos;
    }

    gl_Position = projectMatrix * viewMatrix * modelMatrix * pos;
    FragColor = color;
    FragNormal = mat3(modelMatrix) * aNormal;
}