#pragma once
#include "Scene.h"

class LoginScene : public Scene {
private:
    Model* loginModel;
    ShaderProgram* shader;

public:
    void init() override;
    void update() override; // Overridden to handle rotation
    ~LoginScene();
};