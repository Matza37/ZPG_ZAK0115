#include "TriangleScene.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

void TriangleScene::init() {
    float triangle_points[] = {
         0.0f,  0.5f, 0.0f,       1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,       0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,       0.0f, 0.0f, 1.0f
    };

    Shader vert(GL_VERTEX_SHADER, "shaders/color.vert");
    Shader frag(GL_FRAGMENT_SHADER, "shaders/color.frag");
    shader = new ShaderProgram(&vert, &frag);

    camera = new Camera(shader);
    shader->setCamera(camera);

    triangleModel = new Model(triangle_points, sizeof(triangle_points));

    DrawableObject* triangle = new DrawableObject(triangleModel, shader);
    objects.push_back(triangle);
}

/*
void TriangleScene::update() {
    static float angle = 0.0f;
    angle += 0.02f;

    if (!objects.empty()) {
        glm::mat4 M(1.0f);
        // Nejprve posun, poté rotace kolem počátku (0,0,0)
        M = glm::rotate(M, angle, glm::vec3(0.0f, 0.0f, 1.0f));
        M = glm::translate(M, glm::vec3(0.5f, 0.0f, 0.0f));

        objects[0]->getTransformation().setMatrix(M);
    }
}
/*
/**/
void TriangleScene::update() {
    static float angle = 0.0f;
    angle += 0.02f;

    if (!objects.empty()) {
        glm::mat4 M(1.0f);
        // Nejprve rotace kolem vlastní osy, poté posun stranou
        M = glm::translate(M, glm::vec3(0.5f, 0.0f, 0.0f));
        M = glm::rotate(M, angle, glm::vec3(0.0f, 0.0f, 1.0f));

        objects[0]->getTransformation().setMatrix(M);
    }
}
/**/

TriangleScene::~TriangleScene() {
    delete triangleModel;
    delete shader;
    for (auto obj : objects) delete obj;
}