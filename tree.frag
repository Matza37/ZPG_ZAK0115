#version 330 core
in vec3 vertexColor;
in vec3 normal;

uniform vec3 fragmentColor; // Added to satisfy DrawableObject::draw()
out vec4 FragColor;

void main() {
    float shade = 0.3 + 0.7 * abs(normal.y);
    // Multiply by vertexColor, lighting shade, and the object's fragmentColor tint
    FragColor = vec4(shade * vertexColor * fragmentColor, 1.0);
}