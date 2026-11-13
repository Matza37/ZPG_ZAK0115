#include "LoginScene.h"
#include "text.h"

void LoginScene::init() {
    Shader vert(GL_VERTEX_SHADER, "shaders/basic.vert");
    Shader frag(GL_FRAGMENT_SHADER, "shaders/basic.frag");
    shader = new ShaderProgram(&vert, &frag);

    camera = new Camera(shader);
    shader->setCamera(camera);

    loginModel = new Model(points, sizeof(points));

    DrawableObject* loginObj = new DrawableObject(loginModel, shader);
    loginObj->color = glm::vec3(0.0f, 0.8f, 1.0f); // color
    loginObj->getTransformation().setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    loginObj->getTransformation().setScale(glm::vec3(0.5f));

    objects.push_back(loginObj);
}

void LoginScene::update() {
    for (auto obj : objects) {
        float currentRot = obj->getTransformation().getRotationY();
        obj->getTransformation().setRotationY(currentRot + 0.02f); // rotation
    }
}

LoginScene::~LoginScene() {
    delete loginModel;
    delete shader;
    for (auto obj : objects) delete obj;
}