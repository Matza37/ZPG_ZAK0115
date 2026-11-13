#pragma once
#include "Scene.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "DrawableObject.h"
#include "Texture.h"

class EB408Scene : public Scene {
private:
    ShaderProgram* textureShader;

    // Textury pro jednotlivé objekty
    Texture* eb408Texture;
    Texture* doorTexture;
    Texture* whiteboardTexture;
    Texture* photoTexture;
    Texture* shrekTexture;

    // Modely
    Model* eb408Model;
    Model* doorModel;
    Model* whiteboardModel;
    Model* photoModel;
    Model* shrekModel;

    // Vykreslitelné objekty
    DrawableObject* eb408Object;
    DrawableObject* doorObject;
    DrawableObject* whiteboardObject;
    DrawableObject* photoObject;
    DrawableObject* shrekObject;

public:
    EB408Scene();
    ~EB408Scene() override;

    void init() override;
    void draw() override;
	void spawnObjectAt(const glm::vec3& worldPos) override;
    void spawnMovingObjectBetween(const glm::vec3& pointA, const glm::vec3& pointB) override;
};