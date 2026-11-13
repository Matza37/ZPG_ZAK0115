#pragma once

#include "Scene.h"
#include "ShaderProgram.h"
#include "DrawableObject.h"
#include "Camera.h"
#include "tree.h"
#include "bushes.h"
#include "sphere.h"
#include "plain.h"

class NightForestScene : public Scene {
private:
    Model* treeModel = nullptr;
    Model* bushModel = nullptr;
    Model* fireflyModel = nullptr; // Model pro světlušku
    Model* plainModel = nullptr;

    ShaderProgram* nightShader = nullptr;   // Shader pro osvětlený noční les
    ShaderProgram* fireflyShader = nullptr; // Konstantní shader pro samotnou světlušku (aby zářila nezávisle)
    Camera* camera = nullptr;

    glm::vec3 fireflyPosition; // Aktuální pozice světlušky v prostoru
    float timeAngle = 0.0f;    // Úhel pro animaci pohybu světlušky

public:
    void init() override;
    void update() override;
    ~NightForestScene();
};