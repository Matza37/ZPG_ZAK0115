#version 460 core

in vec3 worldPosition;
in vec3 worldNormal;

uniform vec3 fragmentColor;

out vec4 out_Color;

void main(void) {
    vec3 color = (length(fragmentColor) > 0.0) ? fragmentColor : vec3(0.385, 0.647, 0.812);
    out_Color = vec4(color, 1.0);
}