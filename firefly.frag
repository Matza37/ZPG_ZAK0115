#version 460 core
out vec4 FragColor;

uniform vec3 fragmentColor; 

void main() {
    // Můžeme barvu vynásobit vyšším číslem (např. 2.0), aby zářila jasněji
    FragColor = vec4(fragmentColor * 2.0, 1.0);
}