#include "NightForestScene.h"
#include <cstdlib>
#include <ctime>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

void NightForestScene::init() {
    // 1. Načtení nočního shaderu s útlumem pro les (využívá light.vert pro pozice a normály)
    Shader nightVert(GL_VERTEX_SHADER, "shaders/light.vert");
    Shader nightFrag(GL_FRAGMENT_SHADER, "shaders/night_light.frag");
    nightShader = new ShaderProgram(&nightVert, &nightFrag);

    // Inicializace kamery a propojení s nočním shaderem
    camera = new Camera(nightShader);
    nightShader->setCamera(camera);

    // 2. Načtení jednoduchého konstantního shaderu pro samotnou světlušku (zářící kulička)
    Shader fireflyVert(GL_VERTEX_SHADER, "shaders/firefly.vert");
    Shader fireflyFrag(GL_FRAGMENT_SHADER, "shaders/firefly.frag");
    fireflyShader = new ShaderProgram(&fireflyVert, &fireflyFrag);
    fireflyShader->setCamera(camera);

    // Inicializace modelů (stromy, keře a podlaha vyžadují normály, proto 6 hodnot na vrchol)
    treeModel = new Model(tree, sizeof(tree), 6);
    bushModel = new Model(bushes, sizeof(bushes), 6);
    plainModel = new Model(plain, sizeof(plain), 6);

    // Světluška je obyčejná sféra
    fireflyModel = new Model(sphere, sizeof(sphere), 6);

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // 3. Generování 80 stromů v nočním lese pomocí nightShaderu
    for (int i = 0; i < 80; ++i) {
        DrawableObject* treeObj = new DrawableObject(treeModel, nightShader);

        float posX = ((float)std::rand() / RAND_MAX) * 20.0f - 10.0f; // -10 až 10
        float posZ = -((float)std::rand() / RAND_MAX) * 20.0f - 2.0f; // Blíž ke kameře
        float scaleVal = 0.08f + ((float)std::rand() / RAND_MAX) * 0.08f;
        float rotY = ((float)std::rand() / RAND_MAX) * 360.0f;

        glm::mat4 M(1.0f);
        M = glm::translate(M, glm::vec3(posX, -1.0f, posZ));
        M = glm::rotate(M, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
        M = glm::scale(M, glm::vec3(scaleVal));
        treeObj->getTransformation().setMatrix(M);
        treeObj->color = glm::vec3(0.05f, 0.2f, 0.08f); // Tmavě zelená pro noční les

        objects.push_back(treeObj);
    }

    // 4. Generování 20 keřů pomocí nightShaderu
    for (int i = 0; i < 20; ++i) {
        DrawableObject* bushObj = new DrawableObject(bushModel, nightShader);

        float posX = ((float)std::rand() / RAND_MAX) * 18.0f - 9.0f;
        float posZ = -((float)std::rand() / RAND_MAX) * 18.0f - 1.0f;
        float scaleVal = 0.15f + ((float)std::rand() / RAND_MAX) * 0.25f;
        float rotY = ((float)std::rand() / RAND_MAX) * 360.0f;

        glm::mat4 M(1.0f);
        M = glm::translate(M, glm::vec3(posX, -1.0f, posZ));
        M = glm::rotate(M, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
        M = glm::scale(M, glm::vec3(scaleVal));
        bushObj->getTransformation().setMatrix(M);

        bushObj->color = glm::vec3(0.1f, 0.4f, 0.15f);
        objects.push_back(bushObj);
    }

    // 5. Přidání podlahy (Plain) v úrovni terénu s nočním shaderem
    DrawableObject* floorObj = new DrawableObject(plainModel, nightShader);
    glm::mat4 floorMatrix(1.0f);
    floorMatrix = glm::translate(floorMatrix, glm::vec3(0.0f, -1.0f, -10.0f));
    floorMatrix = glm::scale(floorMatrix, glm::vec3(25.0f, 1.0f, 25.0f));
    floorObj->getTransformation().setMatrix(floorMatrix);
    floorObj->color = glm::vec3(0.1f, 0.2f, 0.1f); // Tmavá noční tráva

    objects.push_back(floorObj);

    // 6. Vytvoření objektu světlušky (zobrazuje se pomocí fireflyShaderu, aby svítila nezávisle)
    DrawableObject* fireflyObj = new DrawableObject(fireflyModel, fireflyShader);
    fireflyObj->color = glm::vec3(1.0f, 0.9f, 0.2f); // Zářivě žlutozelená barva světlušky

    // Uložení ukazatele nebo správa pozice (světlušku budeme posouvat v update)
    fireflyPosition = glm::vec3(0.0f, 1.5f, -3.0f);

    glm::mat4 fireflyMatrix(1.0f);
    fireflyMatrix = glm::translate(fireflyMatrix, fireflyPosition);
    fireflyMatrix = glm::scale(fireflyMatrix, glm::vec3(0.15f)); // Malá kulička jako světluška
    fireflyObj->getTransformation().setMatrix(fireflyMatrix);

    objects.push_back(fireflyObj);
}

void NightForestScene::update() {
    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    float dt = static_cast<float>(currentTime - lastTime);
    lastTime = currentTime;

    if (camera) {
        camera->processKeyboard(dt);
        camera->processMouse();
    }

    // Animace pohybu světlušky (létá v prostoru před lesem v mírném vlnovém kruhu)
    timeAngle += dt * 1.2f;
    fireflyPosition.x = std::sin(timeAngle) * 7.0f;
    fireflyPosition.z = -3.0f + std::cos(timeAngle * 0.8f) * 4.0f;
    fireflyPosition.y = 1.0f + std::sin(timeAngle * 2.0f) * 1.0f;

    // Aktualizace transformační matice světlušky v objektu (poslední objekt v seznamu 'objects' je světluška)
    if (!objects.empty()) {
        DrawableObject* fireflyObj = objects.back();
        glm::mat4 fireflyMatrix(1.0f);
        fireflyMatrix = glm::translate(fireflyMatrix, fireflyPosition);
        fireflyMatrix = glm::scale(fireflyMatrix, glm::vec3(0.15f));
        fireflyObj->getTransformation().setMatrix(fireflyMatrix);
    }

    // Odeslání aktuální pozice světlušky (bodového světla) do nočního shaderu pro výpočet útlumu
    // Odeslání aktuální pozice světlušky (bodového světla) do nočního shaderu pomocí setUniform
    if (nightShader) {
        nightShader->use();
        nightShader->setUniform("lightPosition", fireflyPosition);
        nightShader->unuse();
    }
}

NightForestScene::~NightForestScene() {
    delete treeModel;
    delete bushModel;
    delete fireflyModel;
    delete plainModel;
    delete nightShader;
    delete fireflyShader;
    for (auto obj : objects) delete obj;
}