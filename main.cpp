#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Application.h"

int main(void)
{
    Application* app = new Application();

    app->init();
    app->run();

    delete app;
    return 0;
}