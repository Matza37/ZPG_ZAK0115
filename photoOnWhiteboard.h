#pragma once

// Jednoduchý obdélník (2 trojúhelníky) s pozicí, normálou a UV souřadnicemi
static const float photoOnWhiteboard_vertices[] = {
    // Pozice (X,Y,Z)      // Normála (X,Y,Z)    // UV (U,V)
    -0.5f,  0.5f, 0.0f,    0.0f, 0.0f, 1.0f,    0.0f, 1.0f,
    -0.5f, -0.5f, 0.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
     0.5f, -0.5f, 0.0f,    0.0f, 0.0f, 1.0f,    1.0f, 0.0f,

    -0.5f,  0.5f, 0.0f,    0.0f, 0.0f, 1.0f,    0.0f, 1.0f,
     0.5f, -0.5f, 0.0f,    0.0f, 0.0f, 1.0f,    1.0f, 0.0f,
     0.5f,  0.5f, 0.0f,    0.0f, 0.0f, 1.0f,    1.0f, 1.0f
};