#version 460 core

in vec3 worldPosition;
in vec3 worldNormal;
in vec3 vertexColor;

uniform vec3 fragmentColor; // Přidáno, aby zmizelo varování v konzoli

out vec4 out_Color;

void main(void) {
    // Světelný zdroj je uprostřed, kde se nachází Slunce (0.0, 0.0, 0.0)
    vec3 lightPosition = vec3(0.0, 0.0, 0.0); 
    vec3 lightDir = normalize(lightPosition - worldPosition);
    vec3 normal = normalize(worldNormal);
    
    // Použijeme barvu vrcholu planety (případně fallback na fragmentColor)
    vec3 baseColor = (length(vertexColor) > 0.0) ? vertexColor : ((length(fragmentColor) > 0.0) ? fragmentColor : vec3(0.5));
    
    // Ambientní složka (aby odvrácená strana nebyla úplně černá, jako ve vesmíru)
    vec3 ambient = vec3(0.1, 0.1, 0.1) * baseColor;
    
    // Difúzní složka (Lambert) - svítí strana přivrácená ke Slunci
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * baseColor;
    
    // Zrcadlová složka (Phong)
    vec3 specular = vec3(0.0);
    if (diff > 0.0) {
        vec3 viewDir = normalize(vec3(0.0, 2.0, 5.0) - worldPosition); // Směr ke kameře
        vec3 reflectDir = reflect(-lightDir, normal);
        float shininess = 32.0;
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
        specular = spec * vec3(0.3, 0.3, 0.3); // Jemný odlesk na planetě
    }
    
    out_Color = vec4(ambient + diffuse + specular, 1.0);
}