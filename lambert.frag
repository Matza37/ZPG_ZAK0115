#version 460 core

in vec3 worldPosition;
in vec3 worldNormal;

uniform vec3 fragmentColor;

out vec4 out_Color;

void main(void) {
    vec3 lightPosition = vec3(0.0, 0.0, 0.0); // Světlo v [0, 0, 0]
    vec3 lightDir = normalize(lightPosition - worldPosition);
    vec3 normal = normalize(worldNormal);
    
    vec3 color = (length(fragmentColor) > 0.0) ? fragmentColor : vec3(0.385, 0.647, 0.812);
    
    float diff = max(dot(lightDir, normal), 0.0);
    
    vec3 ambient = vec3(0.1, 0.1, 0.1) * color;
    vec3 diffuse = diff * color;
    
    out_Color = vec4(ambient + diffuse, 1.0);
}