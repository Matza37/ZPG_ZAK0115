#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform vec3 fragmentColor; // Přidáno pro kompatibilitu s DrawableObject

void main() {
    // Vynásobení vzorku textury barvou z DrawableObject
    FragColor = texture(texture1, TexCoord) * vec4(fragmentColor, 1.0);
}