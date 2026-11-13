#pragma once
#include "Scene.h"
#include "ShaderProgram.h"
#include "DrawableObject.h"
#include "Camera.h"
#include "sun.h"
#include "earth.h"
#include "moon.h"
#include "spaceShuttle.h" // Přiložený model raketoplánu

class SolarSystemScene : public Scene {
private:
    Model* sunModel;
    Model* earthModel;
    Model* moonModel;
    Model* shuttleModel; // Model raketoplánu

    ShaderProgram* shuttleShader;
    ShaderProgram* sunShader;
    ShaderProgram* planetShader;
    Camera* camera;

    DrawableObject* sunObj;
    DrawableObject* earthObj;
    DrawableObject* moonObj;
    DrawableObject* shuttleObj; // Objekt raketoplánu

    // Animation angles
    float earthOrbitAngle = 0.0f;
    float earthSelfAngle = 0.0f;
    float moonOrbitAngle = 0.0f;
    float sunSelfAngle = 0.0f;

public:
    void init() override;
    void update() override;
    ~SolarSystemScene();
};