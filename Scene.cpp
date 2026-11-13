#include "Scene.h"
#include <iostream>
#include <algorithm>

void Scene::update() {
    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    float dt = static_cast<float>(currentTime - lastTime);
    lastTime = currentTime;

    // Ochrana proti velkému skoku času při přepnutí scény
    if (dt > 0.1f) dt = 0.1f;

    if (camera) {
        camera->processKeyboard(dt);
        camera->processMouse();
    }

    // 3a) Aktualizace pozice všech pohybujících se objektů: P(t) = A + t * (B - A), t v <0, 1>
    for (auto& m : movingObjects) {
        if (m.object == nullptr) continue;

        float distance = glm::length(m.pointB - m.pointA);
        float step = (distance > 0.001f) ? (m.speed / distance) * dt : 0.0f;

        m.t += m.direction * step;

        if (m.t >= 1.0f) {
            m.t = 1.0f;
            m.direction = -1; // Otočení směru zpět k bodu A
        }
        else if (m.t <= 0.0f) {
            m.t = 0.0f;
            m.direction = 1;  // Otočení směru zpět k bodu B
        }

        glm::vec3 currentPos = m.pointA + m.t * (m.pointB - m.pointA);
        m.object->getTransformation().setPosition(currentPos);
    }
}

void Scene::draw() {
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    for (auto obj : objects) {
        if (obj != nullptr) {
            glStencilFunc(GL_ALWAYS, obj->getID(), 0xFF);
            obj->draw();
        }
    }

    glDisable(GL_STENCIL_TEST);
}

void Scene::handleMovePointClick(const glm::vec3& worldPos) {
    if (!hasFirstMovePoint) {
        firstMovePoint = worldPos;
        hasFirstMovePoint = true;
        std::cout << "Point A saved [" << worldPos.x << ", " << worldPos.y << ", " << worldPos.z
            << "]. Click on the target point B." << std::endl;
    }
    else {
        std::cout << "Point B saved [" << worldPos.x << ", " << worldPos.y << ", " << worldPos.z
            << "]. Creating a moving object." << std::endl;
        spawnMovingObjectBetween(firstMovePoint, worldPos);
        hasFirstMovePoint = false;
    }
}

void Scene::selectObjectByID(GLuint id) {
    // 3b) Kontrola, zda uživatel klikl na pohybující se objekt -> smaže se
    for (auto it = movingObjects.begin(); it != movingObjects.end(); ++it) {
        if (it->object != nullptr && it->object->getID() == id) {
            DrawableObject* target = it->object;

            if (selectedObject == target) {
                selectedObject = nullptr;
            }

            movingObjects.erase(it);
            objects.erase(std::remove(objects.begin(), objects.end(), target), objects.end());
            delete target;

            std::cout << "Moving object with ID " << id << " was deleted!" << std::endl;
            return;
        }
    }

    // Vrácení PŮVODNÍ barvy dříve vybranému statickému objektu
    if (selectedObject != nullptr) {
        selectedObject->color = originalSelectedColor;
        selectedObject = nullptr;
    }

    if (id == 0) {
        std::cout << "Clicked on background (ID 0)." << std::endl;
        return;
    }

    for (auto obj : objects) {
        if (obj != nullptr && obj->getID() == id) {
            selectedObject = obj;
            originalSelectedColor = obj->color; // Uložení původní barvy (např. zelené u plain)
            selectedObject->color = glm::vec3(1.0f, 0.4f, 0.4f);
            std::cout << "Selected static object with ID: " << id << std::endl;
            return;
        }
    }
}