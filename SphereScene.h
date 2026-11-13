#pragma once
#include "Scene.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "DrawableObject.h"
#include "Camera.h"

class SphereScene : public Scene {
private:
    Model* sphereModel = nullptr;
    ShaderProgram* shaderConstant = nullptr;
    ShaderProgram* shaderLambert = nullptr;
    ShaderProgram* shaderPhong = nullptr;
    ShaderProgram* shaderBlinn = nullptr;
    Camera* camera = nullptr;

    float fov = 60.0f;

public:
    void init() override;
    void update() override;
    ~SphereScene();
};