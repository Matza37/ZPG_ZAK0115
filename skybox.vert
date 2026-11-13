#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 viewMatrix;
uniform mat4 projectMatrix;

void main() {
    TexCoords = aPos;
    // Odstranění translace (posunu) z pohledové matice
    mat4 viewNoTranslation = mat4(mat3(viewMatrix));
    vec4 pos = projectMatrix * viewNoTranslation * vec4(aPos, 1.0);
    // Trik pro nastavení hloubky na maximum (1.0)
    gl_Position = pos.xyww;
}