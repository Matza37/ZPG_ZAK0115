#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "Scene.h"

enum class InteractionMode {
    PICK,   // Výběr statických / smazání pohybujících se objektů (klávesa P)
    INSERT, // Vkládání statických objektů (klávesa I)
    MOVE    // Zadání 2 bodů pro pohybující se objekt (klávesa M)
};

class Application {
private:
    GLFWwindow* window;
    Scene* currentScene;

    InteractionMode currentMode;
    bool leftMouseClicked;
    double clickX;
    double clickY;

    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    void handleMouseClick();

public:
    Application();
    ~Application();

    void init();
    void run();
    void switchScene(Scene* newScene);
};