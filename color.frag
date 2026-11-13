#version 330 core
in vec3 vertexColor;
out vec4 FragColor;

uniform vec3 fragmentColor; 

void main() {
    FragColor = vec4(vertexColor * fragmentColor, 1.0);
}