#pragma once
#include "Scene.h"
#include "ShaderProgram.h"
#include "DrawableObject.h"
#include "tree.h"
#include "bushes.h"
#include "sphere.h"
#include "clock.h"
#include "plain.h"

class ForestScene : public Scene {
private:
    Model* treeModel = nullptr;
    Model* bushModel = nullptr;
    Model* sunModel = nullptr;
    Model* clockModelObj = nullptr;
    Model* plainModel = nullptr;

    ShaderProgram* shader = nullptr;
    ShaderProgram* basicShader = nullptr;
    ShaderProgram* clockShader = nullptr;

public:
    void init() override;
    void update() override;
    void spawnObjectAt(const glm::vec3& worldPos) override;
    void spawnMovingObjectBetween(const glm::vec3& pointA, const glm::vec3& pointB) override;
    ~ForestScene() override;
};