#include "Application.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <cstdio>

#include "TriangleScene.h"
#include "SphereScene.h"
#include "ForestScene.h"
#include "LoginScene.h"
#include "SolarSystemScene.h"
#include "ClockScene.h"
#include "NightForestScene.h"
#include "ShrekScene.h"
#include "EB408Scene.h"

Application::Application()
    : window(nullptr), currentScene(nullptr), currentMode(InteractionMode::PICK),
    leftMouseClicked(false), clickX(0.0), clickY(0.0) {}

Application::~Application() {
    if (currentScene) {
        delete currentScene;
    }
    if (window) {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    if (height == 0) height = 1;
    glViewport(0, 0, width, height);
}

void Application::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        if (app != nullptr) {
            glfwGetCursorPos(window, &app->clickX, &app->clickY);
            app->leftMouseClicked = true;
        }
    }
}

void Application::init() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_STENCIL_BITS, 8);

    window = glfwCreateWindow(800, 600, "ZPG - Scenes", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glfwSwapInterval(1);

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        std::cerr << "GLAD initialization failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    switchScene(new EB408Scene());
}

void Application::switchScene(Scene* newScene) {
    if (currentScene != nullptr) {
        delete currentScene;
    }
    DrawableObject::resetIDCounter();
    currentScene = newScene;
    if (currentScene != nullptr) {
        currentScene->init();
    }
}

void Application::handleMouseClick() {
    if (currentScene == nullptr) return;

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    if (height == 0) height = 1;

    GLint x = static_cast<GLint>(clickX);
    GLint y = static_cast<GLint>(clickY);
    int newy = height - y;

    GLbyte color[4];
    GLfloat depth;
    GLuint index;

    glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
    glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

    // Obnovený výpis pozice, barvy (RGBA v hex), hloubky a stencil indexu
    printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n",
        x, y, color[0], color[1], color[2], color[3], depth, index);

    Camera* cam = currentScene->getCamera();
    if (cam != nullptr) {
        float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
        glm::vec3 screenX = glm::vec3(x, newy, depth);
        glm::mat4 view = cam->getViewMatrix();
        glm::mat4 projection = cam->getProjectionMatrix(aspectRatio);
        glm::vec4 viewPort = glm::vec4(0, 0, width, height);

        glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);
        printf("unProject [%f, %f, %f]\n", pos.x, pos.y, pos.z);

        if (currentMode == InteractionMode::PICK) {
            currentScene->selectObjectByID(index);
        }
        else if (currentMode == InteractionMode::INSERT) {
            if (depth < 1.0f) {
                currentScene->spawnObjectAt(pos);
            }
        }
        else if (currentMode == InteractionMode::MOVE) {
            if (depth < 1.0f) {
                currentScene->handleMovePointClick(pos);
            }
            else {
                std::cout << "Outside of Geometry field (depth = 1.0)." << std::endl;
            }
        }
    }
}

void Application::run() {
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // Přepínání scén (1-9)
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) switchScene(new TriangleScene());
        else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) switchScene(new SphereScene());
        else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) switchScene(new ForestScene());
        else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) switchScene(new LoginScene());
        else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) switchScene(new SolarSystemScene());
        else if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) switchScene(new ClockScene());
        else if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS) switchScene(new NightForestScene());
        else if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS) switchScene(new ShrekScene());
        else if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS) switchScene(new EB408Scene());

        // Přepínání režimu kliknutí myši
        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && currentMode != InteractionMode::PICK) {
            currentMode = InteractionMode::PICK;
            if (currentScene) currentScene->resetMoveSelection();
            std::cout << "Mode: PICKING / DELETING MOVING OBJECTS" << std::endl;
        }
        else if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS && currentMode != InteractionMode::INSERT) {
            currentMode = InteractionMode::INSERT;
            if (currentScene) currentScene->resetMoveSelection();
            std::cout << "Mode: INSERTING STATIC OBJECTS" << std::endl;
        }
        else if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS && currentMode != InteractionMode::MOVE) {
            currentMode = InteractionMode::MOVE;
            if (currentScene) currentScene->resetMoveSelection();
            std::cout << "Mode: SETTING MOVEMENT BETWEEN TWO POINTS" << std::endl;
        }

        // Aktualizace, vykreslení scény a zpracování kliknutí myši
        if (currentScene != nullptr) {
            currentScene->update();
            currentScene->draw();

            if (leftMouseClicked) {
                leftMouseClicked = false;
                handleMouseClick();
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}