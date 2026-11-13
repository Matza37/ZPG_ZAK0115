#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 modelMatrix = mat4(1.0);
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectMatrix = mat4(1.0); // Opraveno ze projectionMatrix na projectMatrix

out vec3 worldPosition;
out vec3 worldNormal;

void main(void) {
    vec4 wp = modelMatrix * vec4(position, 1.0f);
    worldPosition = wp.xyz / wp.w;
    worldNormal = normalize(normal);
    
    gl_Position = projectMatrix * viewMatrix * modelMatrix * vec4(position, 1.0f);
}