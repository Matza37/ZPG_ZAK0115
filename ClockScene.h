#pragma once
#include "Scene.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "DrawableObject.h"
#include "Camera.h"
#include "clock.h"

class ClockScene : public Scene {
private:
    Model* clockModelObj = nullptr;
    ShaderProgram* shader = nullptr;
    Camera* camera = nullptr;

public:
    void init() override;
    void update() override;
    ~ClockScene();
};