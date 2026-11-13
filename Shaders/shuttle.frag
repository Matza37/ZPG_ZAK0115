#version 460 core

in vec3 worldPosition;
in vec3 worldNormal;

uniform vec3 fragmentColor;

out vec4 out_Color;

void main(void) {
    // Světlo od Slunce v (0, 0, 0)
    vec3 lightPosition = vec3(0.0, 0.0, 0.0);
    vec3 lightDir = normalize(lightPosition - worldPosition);
    vec3 normal = normalize(worldNormal);
    
    vec3 baseColor = (length(fragmentColor) > 0.0) ? fragmentColor : vec3(0.8, 0.8, 0.8);
    
    vec3 ambient = vec3(0.15, 0.15, 0.15) * baseColor;
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * baseColor;
    
    out_Color = vec4(ambient + diffuse, 1.0);
}