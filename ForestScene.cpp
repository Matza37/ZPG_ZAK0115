#include "ForestScene.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

void ForestScene::init() {
    // 1. Load specialized tree shaders for trees only
    Shader treeVert(GL_VERTEX_SHADER, "shaders/tree.vert");
    Shader treeFrag(GL_FRAGMENT_SHADER, "shaders/tree.frag");
    shader = new ShaderProgram(&treeVert, &treeFrag);

    // Initialize Camera (uses Scene::camera)
    camera = new Camera(shader);
    shader->setCamera(camera);

    treeModel = new Model(tree, sizeof(tree));
    bushModel = new Model(bushes, sizeof(bushes));
    sunModel = new Model(sphere, sizeof(sphere));
    plainModel = new Model(plain, sizeof(plain));
    clockModelObj = new Model(clockModel, sizeof(clockModel), 9);

    // Load clock shaders and link camera
    Shader clockVert(GL_VERTEX_SHADER, "shaders/clock.vert");
    Shader clockFrag(GL_FRAGMENT_SHADER, "shaders/clock.frag");
    clockShader = new ShaderProgram(&clockVert, &clockFrag);
    clockShader->setCamera(camera);

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // 2. Generate 80 Trees using the tree shader
    for (int i = 0; i < 80; ++i) {
        DrawableObject* treeObj = new DrawableObject(treeModel, shader);

        float posX = ((float)std::rand() / RAND_MAX) * 20.0f - 10.0f;
        float posZ = -((float)std::rand() / RAND_MAX) * 20.0f - 2.0f;
        float scaleVal = 0.08f + ((float)std::rand() / RAND_MAX) * 0.08f;
        float rotY = ((float)std::rand() / RAND_MAX) * 360.0f;

        glm::mat4 M(1.0f);
        M = glm::translate(M, glm::vec3(posX, -1.0f, posZ));
        M = glm::rotate(M, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
        M = glm::scale(M, glm::vec3(scaleVal));
        treeObj->getTransformation().setMatrix(M);

        objects.push_back(treeObj);
    }

    // 3. Create basic shader for Bushes, Sun, and Floor
    Shader basicVert(GL_VERTEX_SHADER, "shaders/basic.vert");
    Shader basicFrag(GL_FRAGMENT_SHADER, "shaders/basic.frag");
    basicShader = new ShaderProgram(&basicVert, &basicFrag);
    basicShader->setCamera(camera);

    // 4. Generate 20 Bushes using basicShader
    for (int i = 0; i < 20; ++i) {
        DrawableObject* bushObj = new DrawableObject(bushModel, basicShader);

        float posX = ((float)std::rand() / RAND_MAX) * 18.0f - 9.0f;
        float posZ = -((float)std::rand() / RAND_MAX) * 18.0f - 1.0f;
        float scaleVal = 0.15f + ((float)std::rand() / RAND_MAX) * 0.25f;
        float rotY = ((float)std::rand() / RAND_MAX) * 360.0f;

        glm::mat4 M(1.0f);
        M = glm::translate(M, glm::vec3(posX, -1.0f, posZ));
        M = glm::rotate(M, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
        M = glm::scale(M, glm::vec3(scaleVal));
        bushObj->getTransformation().setMatrix(M);

        bushObj->color = glm::vec3(0.15f, 0.6f, 0.15f);

        objects.push_back(bushObj);
    }

    // 5. Sun object high up in the sky
    DrawableObject* sun = new DrawableObject(sunModel, basicShader);
    sun->getTransformation().setPosition(glm::vec3(0.0f, 30.0f, -45.0f));
    sun->getTransformation().setScale(glm::vec3(3.0f));
    sun->color = glm::vec3(1.0f, 0.9f, 0.2f);

    objects.push_back(sun);

    // 6. Add Floor (Plain) at ground level
    DrawableObject* floorObj = new DrawableObject(plainModel, basicShader);
    glm::mat4 floorMatrix(1.0f);
    floorMatrix = glm::translate(floorMatrix, glm::vec3(0.0f, -1.0f, -10.0f));
    floorMatrix = glm::scale(floorMatrix, glm::vec3(25.0f, 1.0f, 25.0f));
    floorObj->getTransformation().setMatrix(floorMatrix);
    floorObj->color = glm::vec3(0.2f, 0.4f, 0.2f);

    objects.push_back(floorObj);

    // 7. Generate 2 random Clock instances in the forest
    for (int i = 0; i < 2; ++i) {
        DrawableObject* clockObj = new DrawableObject(clockModelObj, clockShader);

        float posX = ((float)std::rand() / RAND_MAX) * 14.0f - 7.0f;
        float posY = ((float)std::rand() / RAND_MAX) * 1.5f + 0.5f;
        float posZ = -((float)std::rand() / RAND_MAX) * 12.0f - 3.0f;

        glm::mat4 M(1.0f);
        M = glm::translate(M, glm::vec3(posX, posY, posZ));
        M = glm::rotate(M, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        M = glm::scale(M, glm::vec3(-0.4f, 0.4f, 0.4f));
        clockObj->getTransformation().setMatrix(M);

        objects.push_back(clockObj);
    }
}

void ForestScene::spawnObjectAt(const glm::vec3& worldPos) {
    if (treeModel == nullptr || shader == nullptr) return;

    DrawableObject* newTree = new DrawableObject(treeModel, shader);
    newTree->getTransformation().setScale(glm::vec3(0.12f));
    newTree->getTransformation().setPosition(worldPos);

    objects.push_back(newTree);

    std::cout << "Vlozen novy strom v lese (ID: " << newTree->getID() << ") na pozici ["
        << worldPos.x << ", " << worldPos.y << ", " << worldPos.z << "]" << std::endl;
}

void ForestScene::spawnMovingObjectBetween(const glm::vec3& pointA, const glm::vec3& pointB) {
    if (bushModel == nullptr || basicShader == nullptr) return;

    DrawableObject* movingBush = new DrawableObject(bushModel, basicShader);
    movingBush->getTransformation().setScale(glm::vec3(0.35f));
    movingBush->getTransformation().setPosition(pointA);
    movingBush->color = glm::vec3(0.9f, 0.5f, 0.1f); // Oranžový keř pro snadné rozlišení

    objects.push_back(movingBush);

    MovingObject mo;
    mo.object = movingBush;
    mo.pointA = pointA;
    mo.pointB = pointB;
    mo.t = 0.0f;
    mo.speed = 2.0f;
    mo.direction = 1;

    movingObjects.push_back(mo);

    std::cout << "Vytvoren pohybujici se ker v lese (ID: " << movingBush->getID() << ")" << std::endl;
}

void ForestScene::update() {
    // Aktualizuje kameru i pohybující se objekty (P(t) = A + t * (B - A))
    Scene::update();

    // Update real-time uniforms for the clock shader
    std::time_t t = std::time(nullptr);
    std::tm now;
#if defined(_MSC_VER)
    localtime_s(&now, &t);
#else
    std::tm* timePtr = std::localtime(&t);
    if (timePtr) now = *timePtr;
    else now = {};
#endif

    float hours = (float)(now.tm_hour % 12) + (float)now.tm_min / 60.0f;
    float minutes = (float)now.tm_min + (float)now.tm_sec / 60.0f;
    float seconds = (float)now.tm_sec;

    float hourAngle = -hours * (2.0f * 3.1415926535f / 12.0f);
    float minAngle = -minutes * (2.0f * 3.1415926535f / 60.0f);
    float secAngle = -seconds * (2.0f * 3.1415926535f / 60.0f);

    if (clockShader) {
        clockShader->use();
        clockShader->setUniform("uHourAngle", hourAngle);
        clockShader->setUniform("uMinAngle", minAngle);
        clockShader->setUniform("uSecAngle", secAngle);
        clockShader->unuse();
    }
}

ForestScene::~ForestScene() {
    delete treeModel;
    delete bushModel;
    delete sunModel;
    delete clockModelObj;
    delete plainModel;
    delete shader;
    delete basicShader;
    delete clockShader;
    for (auto obj : objects) delete obj;
}