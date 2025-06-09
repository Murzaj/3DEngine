#pragma once

#include <GL/glew.h> 
#include <glm/glm.hpp>
#include "TexturedModelShape3D.hpp" 

/// @brief Klasa reprezentuj¹ca trójwymiarow¹, teksturowan¹ p³aszczyznê.
/// 
/// Dziedziczy po TexturedModelShape3D, definiuje prost¹ p³aszczyznê z tekstur¹.
class TexturedPlane3D : public TexturedModelShape3D {
public:

    /// @brief Konstruktor klasy TexturedPlane3D.
    /// @param modulateColor Kolor moduluj¹cy teksturê.
    /// @param textureId Identyfikator tekstury OpenGL.
    ///
    /// Inicjalizuje p³aszczyznê o wymiarach 2x2 jednostki, ustawiaj¹c
    /// wierzcho³ki, normalne, indeksy i wspó³rzêdne tekstury.
    TexturedPlane3D(glm::vec3 modulateColor, GLuint textureId) :
        TexturedModelShape3D(
            {
              -1.0f, 0.0f, -1.0f,
               1.0f, 0.0f, -1.0f,
               1.0f, 0.0f,  1.0f,
              -1.0f, 0.0f,  1.0f,
            },
            std::vector<float>{},
            modulateColor,
            {
              0.0f, 1.0f, 0.0f,
              0.0f, 1.0f, 0.0f,
              0.0f, 1.0f, 0.0f,
              0.0f, 1.0f, 0.0f,
            },
            {
                0, 2, 1,
                0, 3, 2,
            },
            {
                0.0f, 0.0f,
                1.0f, 0.0f,
                1.0f, 1.0f,
                0.0f, 1.0f,
            },
            textureId
            )
    {
    }
};
