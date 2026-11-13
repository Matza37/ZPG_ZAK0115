#include "SolarSystemScene.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

void SolarSystemScene::init() {
    // Zapnutí hloubkového bufferu[cite: 25]
    glEnable(GL_DEPTH_TEST);

    // Načtení shaderů
    Shader sunVert(GL_VERTEX_SHADER, "shaders/color.vert");
    Shader sunFrag(GL_FRAGMENT_SHADER, "shaders/color.frag");
    sunShader = new ShaderProgram(&sunVert, &sunFrag);

    Shader planetVert(GL_VERTEX_SHADER, "shaders/phong_color.vert");
    Shader planetFrag(GL_FRAGMENT_SHADER, "shaders/phong_color.frag");
    planetShader = new ShaderProgram(&planetVert, &planetFrag);

    Shader shuttleVert(GL_VERTEX_SHADER, "shaders/shuttle.vert");
    Shader shuttleFrag(GL_FRAGMENT_SHADER, "shaders/shuttle.frag");
    shuttleShader = new ShaderProgram(&shuttleVert, &shuttleFrag);

    // 1. Inicializace kamery MUSÍ BÝT PRVNÍ, než ji přiřadíme shaderům
    camera = new Camera(sunShader);
    camera->setPosition(glm::vec3(0.0f, 2.0f, 5.0f));

    // 2. Propojení kamery se všemi shadery
    sunShader->setCamera(camera);
    planetShader->setCamera(camera);
    shuttleShader->setCamera(camera);

    // Inicializace modelů (6 hodnot na vrchol: pozice + barva/normála)
    sunModel = new Model(sunVertices, sizeof(sunVertices), 6);
    earthModel = new Model(earthVertices, sizeof(earthVertices), 6);
    moonModel = new Model(moonVertices, sizeof(moonVertices), 6);
    shuttleModel = new Model(spaceShuttle, sizeof(spaceShuttle), 6);

    // Vytvoření objektů
    sunObj = new DrawableObject(sunModel, sunShader);
    earthObj = new DrawableObject(earthModel, planetShader);
    moonObj = new DrawableObject(moonModel, planetShader);
    shuttleObj = new DrawableObject(shuttleModel, shuttleShader);

    shuttleObj->color = glm::vec3(0.85f, 0.85f, 0.85f); // Stříbřitá barva

    // Umístění raketoplánu staticky do prostoru
    glm::mat4 shuttleMatrix = glm::mat4(1.0f);
    shuttleMatrix = glm::translate(shuttleMatrix, glm::vec3(3.5f, 1.0f, 1.5f));
    shuttleMatrix = glm::scale(shuttleMatrix, glm::vec3(0.4f));
    shuttleObj->getTransformation().setMatrix(shuttleMatrix);

    objects.push_back(sunObj);
    objects.push_back(earthObj);
    objects.push_back(moonObj);
    objects.push_back(shuttleObj);
}

void SolarSystemScene::update() {
    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    float dt = static_cast<float>(currentTime - lastTime);
    lastTime = currentTime;

    if (camera) {
        camera->processKeyboard(dt);
        camera->processMouse();
    }

    // Animace úhlů pro planety
    earthOrbitAngle += 0.008f;
    earthSelfAngle += 0.02f;
    moonOrbitAngle += 0.03f;
    sunSelfAngle += 0.002f;

    // 1. SUN MATRIX
    glm::mat4 sunMatrix = glm::mat4(1.0f);
    sunMatrix = glm::rotate(sunMatrix, sunSelfAngle, glm::vec3(0.0f, 1.0f, 0.0f));
    sunMatrix = glm::scale(sunMatrix, glm::vec3(0.6f));
    sunObj->getTransformation().setMatrix(sunMatrix);

    // 2. EARTH MATRIX
    glm::mat4 earthMatrix = glm::mat4(1.0f);
    earthMatrix = glm::rotate(earthMatrix, earthOrbitAngle, glm::vec3(0.0f, 1.0f, 0.0f));
    earthMatrix = glm::translate(earthMatrix, glm::vec3(2.5f, 0.0f, 0.0f));
    earthMatrix = glm::rotate(earthMatrix, earthSelfAngle, glm::vec3(0.0f, 1.0f, 0.0f));
    earthMatrix = glm::scale(earthMatrix, glm::vec3(0.3f));
    earthObj->getTransformation().setMatrix(earthMatrix);

    // 3. MOON MATRIX
    glm::mat4 moonMatrix = glm::mat4(1.0f);
    moonMatrix = glm::rotate(moonMatrix, earthOrbitAngle, glm::vec3(0.0f, 1.0f, 0.0f));
    moonMatrix = glm::translate(moonMatrix, glm::vec3(2.5f, 0.0f, 0.0f));
    moonMatrix = glm::rotate(moonMatrix, moonOrbitAngle, glm::vec3(0.0f, 1.0f, 0.0f));
    moonMatrix = glm::translate(moonMatrix, glm::vec3(0.8f, 0.0f, 0.0f));
    moonMatrix = glm::scale(moonMatrix, glm::vec3(0.12f));
    moonObj->getTransformation().setMatrix(moonMatrix);
}

SolarSystemScene::~SolarSystemScene() {
    delete sunModel;
    delete earthModel;
    delete moonModel;
    delete shuttleModel;
    delete sunShader;
    delete planetShader;
    delete shuttleShader; // Přidáno smazání shaderu raketoplánu
    for (auto obj : objects) delete obj;
}