#include "ShrekScene.h"
#include "shrek.h"
#include "fiona.h"
#include "skybox.h"
#include "toiled.h"

ShrekScene::ShrekScene()
    : textureShader(nullptr), shrekTexture(nullptr), fionaTexture(nullptr), skyboxTexture(nullptr), toiledTexture(nullptr), shrekModel(nullptr), fionaModel(nullptr), toiledModel(nullptr), skyboxModel(nullptr) {}

ShrekScene::~ShrekScene() {
    delete textureShader;
    delete shrekTexture;
    delete fionaTexture;
    delete toiledTexture;
    delete shrekModel;
    delete fionaModel;
    delete toiledModel;
    delete skyboxTexture;
    delete skyboxModel;
    // Všechny DrawableObjects v poli objects smaže základní třída Scene::~Scene()
}

void ShrekScene::init() {
    // 1. Inicializace ShaderProgramu a Kamery
    Shader* vertShader = new Shader(GL_VERTEX_SHADER, "shaders/texture.vert");
    Shader* fragShader = new Shader(GL_FRAGMENT_SHADER, "shaders/texture.frag");
    textureShader = new ShaderProgram(vertShader, fragShader);
    delete vertShader;
    delete fragShader;

    Shader* vertShaderSkybox = new Shader(GL_VERTEX_SHADER, "shaders/skybox.vert");
    Shader* fragShaderSkybox = new Shader(GL_FRAGMENT_SHADER, "shaders/skybox.frag");
    skyboxShader = new ShaderProgram(vertShaderSkybox, fragShaderSkybox);
    delete vertShaderSkybox;
    delete fragShaderSkybox;

    camera = new Camera(textureShader);
    camera->setPosition(glm::vec3(0.0f, 2.0f, 6.0f));

    // 2. Načtení RŮZNÝCH textur
    shrekTexture = new Texture("textures/shrek.png");
    fionaTexture = new Texture("textures/fiona.png"); // Změňte na vaši druhou texturu
    toiledTexture = new Texture("textures/toiled.jpg");

	std::vector<std::string> skyboxFaces = {
        "textures/posx.jpg",
        "textures/negx.jpg",
        "textures/posy.jpg",
        "textures/negy.jpg",
        "textures/posz.jpg",
        "textures/negz.jpg"
	};
    skyboxTexture = new CubemapTexture(skyboxFaces);

    // 3. Načtení RŮZNÝCH modelů
    shrekModel = new Model(shrek_vertices, sizeof(shrek_vertices), 8);
    fionaModel = new Model(fiona_vertices, sizeof(fiona_vertices), 8); // Váš druhý model
    toiledModel = new Model(toiled_vertices, sizeof(toiled_vertices), 8);
    skyboxModel = new Model(skybox_vertices, sizeof(skybox_vertices), 8);

    // 4. Vytvoření 1. objektu (Shrek)
    DrawableObject* shrekObj = new DrawableObject(shrekModel, textureShader, shrekTexture);
    shrekObj->getTransformation().setPosition(glm::vec3(-2.0f, 0.0f, 0.0f));
    objects.push_back(shrekObj);

    // 5. Vytvoření 2. objektu (Fiona)
    DrawableObject* fionaObj = new DrawableObject(fionaModel, textureShader, fionaTexture);
    fionaObj->getTransformation().setPosition(glm::vec3(2.0f, 0.0f, 0.0f));
    objects.push_back(fionaObj);

    // 3. Vytvoření 3. objektu (Toiled)
    DrawableObject* toiledObj = new DrawableObject(toiledModel, textureShader, toiledTexture);
    toiledObj->getTransformation().setPosition(glm::vec3(0.25f, 0.0f, 0.0f));
    objects.push_back(toiledObj);
}

void ShrekScene::draw() {
    textureShader->use();
    if (camera != nullptr) {
        camera->updateMatrices(textureShader);
    }

    // Každý objekt si při volání Scene::draw() sám naváže svou texturu z kroků výše!
    Scene::draw();

    // 2. Vykreslení Skyboxu
    glDepthFunc(GL_LEQUAL); // Změna porovnávání hloubky pro skybox
    skyboxShader->use();
    if (camera != nullptr) {
        camera->updateMatrices(skyboxShader);
    }

    skyboxTexture->bind(0);
    skyboxShader->setUniform("skybox", 0);

    skyboxModel->draw();
    glDepthFunc(GL_LESS); // Navrácení výchozího hloubkového testu
}