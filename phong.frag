#version 460 core

in vec3 worldPosition;
in vec3 worldNormal;

uniform vec3 fragmentColor;

out vec4 out_Color;

void main(void) {
    vec3 lightPosition = vec3(0.0, 10.0, 0.0);
    vec3 lightDir = normalize(lightPosition - worldPosition);
    vec3 normal = normalize(worldNormal);
    
    vec3 color = (length(fragmentColor) > 0.0) ? fragmentColor : vec3(0.385, 0.647, 0.812);
    
    vec3 ambient = vec3(0.1, 0.1, 0.1) * color;
    
    // Difúzní složka
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;
    
    // SPRÁVNĚ: Zrcadlová složka se počítá POUZE pokud na povrch dopadá světlo (diff > 0)
    vec3 specular = vec3(0.0);
    if (diff > 0.0) {
        vec3 viewDir = normalize(vec3(0.0, 0.0, 3.0) - worldPosition);
        vec3 reflectDir = reflect(-lightDir, normal);
        float shininess = 32.0; // Realističtější ostrý lesk
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
        specular = spec * vec3(1.0, 1.0, 1.0);
    }
    
    out_Color = vec4(ambient + diffuse + specular, 1.0);
}