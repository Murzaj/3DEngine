#pragma once

#include <GL/glew.h>
#include "TexturedModelShape3D.hpp"

/// @brief Reprezentuje sze�cienny model 3D z tekstur�.
///
/// Klasa dziedziczy po `TexturedModelShape3D` i definiuje wierzcho�ki, normalne,
/// indeksy oraz wsp�rz�dne tekstury sze�cianu. Mo�e by� u�ywana do renderowania
/// obiekt�w w grze, takich jak platformy, �ciany lub inne prostopad�o�ciany.
class CubeModel3D : public TexturedModelShape3D {
public:

    /// @brief Tworzy nowy sze�cian z przypisan� tekstur�.
    ///
    /// W konstruktorze zdefiniowane s� dane geometrii sze�cianu: pozycje wierzcho�k�w,
    /// normalne, indeksy oraz wsp�rz�dne tekstury dla ka�dej �ciany.
    ///
    /// @param textureId Identyfikator tekstury OpenGL u�ywanej przez model.
    CubeModel3D(GLuint textureId) : TexturedModelShape3D(
        {
            // Wierzcho�ki sze�cianu
            -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f,
            -0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,  0.5f, -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f, -0.5f
        },
        std::vector<float>{}, // Brak kolor�w � u�ywana tekstura
        glm::vec3(1.0f),      // Kolor modulacji (bia�y � nie zmienia tekstury)
        {
            // Normalne do ka�dej �ciany (po 4 normalne na 6 �cian)
            0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,
            0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
            0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
            1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
           -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f
        },
        {
            // Indeksy tr�jk�t�w (2 tr�jk�ty na �cian�, 6 �cian)
            0, 1, 2,   0, 2, 3,
            4, 5, 6,   4, 6, 7,
            8, 9,10,   8,10,11,
           12,13,14,  12,14,15,
           16,17,18,  16,18,19,
           20,21,22,  20,22,23
        },
        {
            // Wsp�rz�dne tekstury (UV) dla ka�dego wierzcho�ka
            0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f
        },
        textureId
    ) {
    }
};
