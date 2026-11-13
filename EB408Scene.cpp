#include "EB408Scene.h"
#include "EB408.h"
#include "door.h"
#include "whiteboard.h"
#include "photoOnWhiteboard.h"
#include "shrek.h"
#include <iostream>

EB408Scene::EB408Scene()
    : textureShader(nullptr),
    eb408Texture(nullptr), doorTexture(nullptr), whiteboardTexture(nullptr), photoTexture(nullptr), shrekTexture(nullptr),
    eb408Model(nullptr), doorModel(nullptr), whiteboardModel(nullptr), photoModel(nullptr), shrekModel(nullptr),
    eb408Object(nullptr), doorObject(nullptr), whiteboardObject(nullptr), photoObject(nullptr), shrekObject(nullptr) {}

EB408Scene::~EB408Scene() {
    for (auto obj : objects) {
        delete obj;
    }
    objects.clear();

    delete textureShader;

    delete eb408Texture;
    delete doorTexture;
    delete whiteboardTexture;
    delete photoTexture;
    delete shrekTexture;

    delete eb408Model;
    delete doorModel;
    delete whiteboardModel;
    delete photoModel;
    delete shrekModel;
}

void EB408Scene::init() {
    // 1. Vytvoření ShaderProgramu pro texturované objekty
    Shader* vertShader = new Shader(GL_VERTEX_SHADER, "shaders/texture.vert");
    Shader* fragShader = new Shader(GL_FRAGMENT_SHADER, "shaders/texture.frag");
    textureShader = new ShaderProgram(vertShader, fragShader);
    delete vertShader;
    delete fragShader;

    // 2. Inicializace kamery
    camera = new Camera(textureShader);
    camera->setPosition(glm::vec3(0.0f, 2.0f, 5.0f));

    // 3. Načtení textur pro jednotlivé modely
    eb408Texture = new Texture("textures/T_EB408.png");
    doorTexture = new Texture("textures/T_door_basecolor.png");
    whiteboardTexture = new Texture("textures/T_Whiteboard_BaseColor.png");
    photoTexture = new Texture("textures/photoOnWhiteboard.png");
    shrekTexture = new Texture("textures/shrek.png");

    // 4. Načtení modelů z .h souborů (8 hodnot na vrchol: 3x pos, 3x normal, 2x UV)
    eb408Model = new Model(EB408_vertices, sizeof(EB408_vertices), 8);
    doorModel = new Model(door_vertices, sizeof(door_vertices), 8);
    whiteboardModel = new Model(whiteboard_vertices, sizeof(whiteboard_vertices), 8);
    photoModel = new Model(photoOnWhiteboard_vertices, sizeof(photoOnWhiteboard_vertices), 8);
    shrekModel = new Model(shrek_vertices, sizeof(shrek_vertices), 8);

    // 5. Propojení modelů, shaderu a textur do samostatných DrawableObjectů
    eb408Object = new DrawableObject(eb408Model, textureShader, eb408Texture);
    doorObject = new DrawableObject(doorModel, textureShader, doorTexture);
    whiteboardObject = new DrawableObject(whiteboardModel, textureShader, whiteboardTexture);
    photoObject = new DrawableObject(photoModel, textureShader, photoTexture);
    shrekObject = new DrawableObject(shrekModel, textureShader, shrekTexture);

    // --- ÚPRAVA DVEŘÍ ---
    doorObject->getTransformation().setScale(glm::vec3(0.01f, 0.01f, 0.01f));
    doorObject->getTransformation().setPosition(glm::vec3(-2.42f, 0.0f, 7.8f));

    // --- ÚPRAVA TABULE ---
    whiteboardObject->getTransformation().setScale(glm::vec3(1.2f, 1.2f, 1.2f));
    whiteboardObject->getTransformation().setPosition(glm::vec3(-3.85f, 0.0f, 5.0f));

    // --- ÚPRAVA FOTKY NA TABULI ---
    photoObject->getTransformation().setScale(glm::vec3(1.2f, 0.8f, 1.2f));
    photoObject->getTransformation().setPosition(glm::vec3(-3.81f, 1.95f, 5.0f));
    photoObject->getTransformation().setRotationY(glm::radians(90.0f));

    // --- ÚPRAVA SHREKA V UČEBNĚ ---
    shrekObject->getTransformation().setPosition(glm::vec3(-2.0f, 0.0f, 3.0f));
    shrekObject->getTransformation().setRotationY(glm::radians(45.0f));

    // 6. Registrace objektů do scény
    objects.push_back(eb408Object);
    objects.push_back(doorObject);
    objects.push_back(whiteboardObject);
    objects.push_back(photoObject);
    objects.push_back(shrekObject);
}

void EB408Scene::spawnObjectAt(const glm::vec3& worldPos) {
    if (shrekModel == nullptr || textureShader == nullptr || shrekTexture == nullptr) return;

    DrawableObject* newShrek = new DrawableObject(shrekModel, textureShader, shrekTexture);
    newShrek->getTransformation().setScale(glm::vec3(0.4f, 0.4f, 0.4f));
    newShrek->getTransformation().setPosition(worldPos);

    objects.push_back(newShrek);

    std::cout << "New Shrek inserted (ID: " << newShrek->getID() << ") on position: ["
        << worldPos.x << ", " << worldPos.y << ", " << worldPos.z << "]" << std::endl;
}

void EB408Scene::spawnMovingObjectBetween(const glm::vec3& pointA, const glm::vec3& pointB) {
    if (shrekModel == nullptr || textureShader == nullptr || shrekTexture == nullptr) return;

    DrawableObject* movingShrek = new DrawableObject(shrekModel, textureShader, shrekTexture);
    movingShrek->getTransformation().setScale(glm::vec3(0.4f, 0.4f, 0.4f));
    movingShrek->getTransformation().setPosition(pointA);

    objects.push_back(movingShrek);

    MovingObject mo;
    mo.object = movingShrek;
    mo.pointA = pointA;
    mo.pointB = pointB;
    mo.t = 0.0f;
    mo.speed = 2.0f; // Rychlost 2 jednotky za sekundu
    mo.direction = 1;

    movingObjects.push_back(mo);

    std::cout << "Moving Shrek created (ID: " << movingShrek->getID() << ")" << std::endl;
}

void EB408Scene::draw() {
    textureShader->use();
    if (camera != nullptr) {
        camera->updateMatrices(textureShader);
    }

    // Vykreslení všech objektů v poli objects
    Scene::draw();
}