#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectMatrix;

out vec3 vertexColor;
out vec3 normal;

void main() {
    // Split tree geometry into leaves and trunk using Vertex ID 
    // (Note: Adjust 36443 if your tree.h has a different vertex count threshold)
    if (gl_VertexID > 36443) {
        vertexColor = vec3(0.1f, 0.6f, 0.2f); // Leaves (Green)
    } else {
        vertexColor = vec3(0.45f, 0.25f, 0.1f); // Trunk (Brown)
    }

    normal = aNormal;
    gl_Position = projectMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
}