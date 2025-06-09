#pragma once

#include <GL/glew.h>
#include "TexturedModelShape3D.hpp"

/// @brief Reprezentuje szeœcienny model 3D z tekstur¹.
///
/// Klasa dziedziczy po `TexturedModelShape3D` i definiuje wierzcho³ki, normalne,
/// indeksy oraz wspó³rzêdne tekstury szeœcianu. Mo¿e byæ u¿ywana do renderowania
/// obiektów w grze, takich jak platformy, œciany lub inne prostopad³oœciany.
class CubeModel3D : public TexturedModelShape3D {
public:

    /// @brief Tworzy nowy szeœcian z przypisan¹ tekstur¹.
    ///
    /// W konstruktorze zdefiniowane s¹ dane geometrii szeœcianu: pozycje wierzcho³ków,
    /// normalne, indeksy oraz wspó³rzêdne tekstury dla ka¿dej œciany.
    ///
    /// @param textureId Identyfikator tekstury OpenGL u¿ywanej przez model.
    CubeModel3D(GLuint textureId) : TexturedModelShape3D(
        {
            // Wierzcho³ki szeœcianu
            -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f,
            -0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,  0.5f, -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f, -0.5f
        },
        std::vector<float>{}, // Brak kolorów — u¿ywana tekstura
        glm::vec3(1.0f),      // Kolor modulacji (bia³y — nie zmienia tekstury)
        {
            // Normalne do ka¿dej œciany (po 4 normalne na 6 œcian)
            0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,
            0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
            0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
            1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
           -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f
        },
        {
            // Indeksy trójk¹tów (2 trójk¹ty na œcianê, 6 œcian)
            0, 1, 2,   0, 2, 3,
            4, 5, 6,   4, 6, 7,
            8, 9,10,   8,10,11,
           12,13,14,  12,14,15,
           16,17,18,  16,18,19,
           20,21,22,  20,22,23
        },
        {
            // Wspó³rzêdne tekstury (UV) dla ka¿dego wierzcho³ka
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
