#pragma once
#include "Scene.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "DrawableObject.h"

class TriangleScene : public Scene {
private:
    Model* triangleModel = nullptr;
    ShaderProgram* shader = nullptr;

public:
    void init() override;
    void update() override; // <-- Add this declaration here!
    ~TriangleScene();
};