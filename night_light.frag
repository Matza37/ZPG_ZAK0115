#version 460 core

in vec3 worldPosition;
in vec3 worldNormal;

uniform vec3 fragmentColor;
uniform vec3 lightPosition;

out vec4 out_Color;

void main(void) {
    vec3 normal = normalize(worldNormal);
    vec3 lightDir = normalize(lightPosition - worldPosition);
    
    // Vzdálenost fragmentu od světlušky
    float distance = length(lightPosition - worldPosition);
    
    // Útlum světla (konstantní, lineární, kvadratický)
    float kc = 1.0f;
    float kl = 0.05f;
    float kq = 0.05f;
    float attenuation = 1.0f / (kc + kl * distance + kq * (distance * distance));
    
    // SVĚTLE ZELENÁ BARVA: Pokud objekt nemá vlastní barvu, použijeme reálnou světle zelenou
    vec3 baseColor = (length(fragmentColor) > 0.0) ? fragmentColor : vec3(0.3f, 0.7f, 0.3f);
    
    // Noční ambientní složka (jemně nazelenalá, aby noc nebyla mrtvá)
    vec3 ambient = vec3(0.05, 0.1f, 0.05) * baseColor;
    
    // Difúzní složka (Lambert) osvětlená světluškou
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * baseColor * vec3(0.9, 1.0, 0.4); // Světluška dává teplé nažloutlé světlo
    
    diffuse *= attenuation;
    
    out_Color = vec4(ambient + diffuse, 1.0);
}