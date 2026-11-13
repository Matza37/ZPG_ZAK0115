#pragma once
#include "Scene.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "DrawableObject.h"
#include "Texture.h"
#include "CubemapTexture.h"

class ShrekScene : public Scene {
private:
    ShaderProgram* textureShader;
    ShaderProgram* skyboxShader;

    // Více textur
    Texture* shrekTexture;
    Texture* fionaTexture; // nebo např. woodTexture, terrainTexture atd.
    Texture* toiledTexture;
    CubemapTexture* skyboxTexture;

    // Více modelů
    Model* shrekModel;
    Model* fionaModel;
    Model* toiledModel;
    Model* skyboxModel;

    DrawableObject* shrekObject;

public:
    ShrekScene();
    ~ShrekScene() override;

    void init() override;
    void draw() override;
};