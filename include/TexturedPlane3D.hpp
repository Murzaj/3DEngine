#pragma once

#include <GL/glew.h> 
#include <glm/glm.hpp>
#include "TexturedModelShape3D.hpp" 

/// @brief Klasa reprezentuj�ca tr�jwymiarow�, teksturowan� p�aszczyzn�.
/// 
/// Dziedziczy po TexturedModelShape3D, definiuje prost� p�aszczyzn� z tekstur�.
class TexturedPlane3D : public TexturedModelShape3D {
public:

    /// @brief Konstruktor klasy TexturedPlane3D.
    /// @param modulateColor Kolor moduluj�cy tekstur�.
    /// @param textureId Identyfikator tekstury OpenGL.
    ///
    /// Inicjalizuje p�aszczyzn� o wymiarach 2x2 jednostki, ustawiaj�c
    /// wierzcho�ki, normalne, indeksy i wsp�rz�dne tekstury.
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
