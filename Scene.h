#pragma once
#include <vector>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "DrawableObject.h"
#include "Camera.h"

struct MovingObject {
    DrawableObject* object;
    glm::vec3 pointA;
    glm::vec3 pointB;
    float t;          // Parametr v rozsahu <0, 1>
    float speed;      // Rychlost pohybu (jednotky za sekundu)
    int direction;    // 1 = směr A -> B, -1 = směr B -> A
};

class Scene {
protected:
    std::vector<DrawableObject*> objects;
    std::vector<MovingObject> movingObjects;
    Camera* camera;
    DrawableObject* selectedObject;
    glm::vec3 originalSelectedColor;

    bool hasFirstMovePoint;
    glm::vec3 firstMovePoint;

public:
    Scene()
        : camera(nullptr), selectedObject(nullptr), originalSelectedColor(1.0f),
        hasFirstMovePoint(false), firstMovePoint(0.0f) {}

    virtual ~Scene() {
        movingObjects.clear();
        if (camera) delete camera;
    }

    virtual void init() = 0;

    virtual void update();
    virtual void draw();

    // Virtuální metody pro vkládání objektů v konkrétních scénách
    virtual void spawnObjectAt(const glm::vec3& worldPos) {}
    virtual void spawnMovingObjectBetween(const glm::vec3& pointA, const glm::vec3& pointB) {}

    void handleMovePointClick(const glm::vec3& worldPos);
    void resetMoveSelection() { hasFirstMovePoint = false; }

    void selectObjectByID(GLuint id);
    DrawableObject* getSelectedObject() const { return selectedObject; }
    Camera* getCamera() const { return camera; }
};