#include "SphereScene.h"
#include "sphere.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

void SphereScene::init() {
    glEnable(GL_DEPTH_TEST);

    Shader vert(GL_VERTEX_SHADER, "shaders/light.vert");
    Shader fragConstant(GL_FRAGMENT_SHADER, "shaders/constant.frag");
    Shader fragLambert(GL_FRAGMENT_SHADER, "shaders/lambert.frag");
    Shader fragPhong(GL_FRAGMENT_SHADER, "shaders/phong.frag");
    Shader fragBlinn(GL_FRAGMENT_SHADER, "shaders/blinn.frag");

    shaderConstant = new ShaderProgram(&vert, &fragConstant);
    shaderLambert = new ShaderProgram(&vert, &fragLambert);
    shaderPhong = new ShaderProgram(&vert, &fragPhong);
    shaderBlinn = new ShaderProgram(&vert, &fragBlinn);

    camera = new Camera(shaderConstant);
    shaderConstant->setCamera(camera);
    shaderLambert->setCamera(camera);
    shaderPhong->setCamera(camera);
    shaderBlinn->setCamera(camera);

    camera->setPosition(glm::vec3(0.0f, 0.0f, 3.0f));

    // Nastavení počátečního FOV
    camera->setFov(60.0f);

    camera->updateMatrices(shaderConstant);
    camera->updateMatrices(shaderLambert);
    camera->updateMatrices(shaderPhong);
    camera->updateMatrices(shaderBlinn);

    sphereModel = new Model(sphere, sizeof(sphere), 6);
    glm::vec3 sphereColor = glm::vec3(0.3f, 0.6f, 0.8f);

    // Vytvoření objektů koulí (stejně jako dříve)...
    // 1. Horní koule (Konstantní)
    {
        DrawableObject* obj = new DrawableObject(sphereModel, shaderPhong);
        glm::mat4 M(1.0f);
        M = glm::translate(M, glm::vec3(0.0f, 0.8f, 0.0f));
        M = glm::scale(M, glm::vec3(0.5f));
        obj->getTransformation().setMatrix(M);
        obj->color = sphereColor;
        objects.push_back(obj);
    }
    // 2. Dolní koule (Lambert)
    {
        DrawableObject* obj = new DrawableObject(sphereModel, shaderPhong);
        glm::mat4 M(1.0f);
        M = glm::translate(M, glm::vec3(0.0f, -0.8f, 0.0f));
        M = glm::scale(M, glm::vec3(0.5f));
        obj->getTransformation().setMatrix(M);
        obj->color = sphereColor;
        objects.push_back(obj);
    }
    // 3. Levá koule (Phong)
    {
        DrawableObject* obj = new DrawableObject(sphereModel, shaderPhong);
        glm::mat4 M(1.0f);
        M = glm::translate(M, glm::vec3(-0.8f, 0.0f, 0.0f));
        M = glm::scale(M, glm::vec3(0.5f));
        obj->getTransformation().setMatrix(M);
        obj->color = sphereColor;
        objects.push_back(obj);
    }
    // 4. Pravá koule (Blinn-Phong)
    {
        DrawableObject* obj = new DrawableObject(sphereModel, shaderPhong);
        glm::mat4 M(1.0f);
        M = glm::translate(M, glm::vec3(0.8f, 0.0f, 0.0f));
        M = glm::scale(M, glm::vec3(0.5f));
        obj->getTransformation().setMatrix(M);
        obj->color = sphereColor;
        objects.push_back(obj);
    }
}

void SphereScene::update() {
    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    float dt = static_cast<float>(currentTime - lastTime);
    lastTime = currentTime;

    if (camera) {
        camera->processKeyboard(dt);
        camera->processMouse();

        // Aktualizace matic pro všechny shadery v této scéně najednou
        camera->updateMatrices(shaderConstant);
        camera->updateMatrices(shaderLambert);
        camera->updateMatrices(shaderPhong);
        camera->updateMatrices(shaderBlinn);
    }
}

SphereScene::~SphereScene() {
    delete sphereModel;
    delete shaderConstant;
    delete shaderLambert;
    delete shaderPhong;
    delete shaderBlinn;
    for (auto obj : objects) {
        delete obj;
    }
}