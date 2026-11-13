#include "ClockScene.h"
#include "clock.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <ctime>

void ClockScene::init() {
    Shader vert(GL_VERTEX_SHADER, "shaders/clock.vert");
    Shader frag(GL_FRAGMENT_SHADER, "shaders/clock.frag");
    shader = new ShaderProgram(&vert, &frag);

    camera = new Camera(shader);
    shader->setCamera(camera);

    // Pozice kamery
    camera->setPosition(glm::vec3(0.0f, 0.0f, 2.5f));

    // Vytvoření modelu hodin
    clockModelObj = new Model(clockModel, sizeof(clockModel), 9);
    DrawableObject* clockObj = new DrawableObject(clockModelObj, shader);

    // Otočení hodin o 180 stupňů kolem osy Y, aby byly otočené dopředu k vám
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(-1.0f, 1.0f, 1.0f));
    clockObj->getTransformation().setMatrix(modelMatrix);

    objects.push_back(clockObj);
}

void ClockScene::update() {
    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    float dt = static_cast<float>(currentTime - lastTime); // Opraveno ze static_format na static_cast
    lastTime = currentTime;

    if (camera) {
        camera->processKeyboard(dt);
        camera->processMouse();
    }

    // Získání reálného času
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

    // Výpočet úhlů
    float hourAngle = -hours * (2.0f * 3.1415926535f / 12.0f);
    float minAngle = -minutes * (2.0f * 3.1415926535f / 60.0f);
    float secAngle = -seconds * (2.0f * 3.1415926535f / 60.0f);

    shader->use();
    shader->setUniform("uHourAngle", hourAngle);
    shader->setUniform("uMinAngle", minAngle);
    shader->setUniform("uSecAngle", secAngle);
    shader->unuse();
}

ClockScene::~ClockScene() {
    delete clockModelObj;
    delete shader;
    for (auto obj : objects) delete obj;
}