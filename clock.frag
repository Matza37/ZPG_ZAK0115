#version 330 core

in vec3 FragColor;
in vec3 FragNormal;

uniform vec3 fragmentColor;

out vec4 FinalColor;

void main() {
    vec3 baseColor = (length(FragColor) > 0.1) ? FragColor : fragmentColor;

    vec3 lightDir = normalize(vec3(0.0, 1.0, 1.0));
    float diff = max(dot(normalize(FragNormal), lightDir), 0.4); 
    
    FinalColor = vec4(baseColor * diff, 1.0);
}