#pragma once

#include <GL/glew.h> 
#include <glm/glm.hpp>
#include "TransformableObject.hpp" 

/// @brief Abstrakcyjna klasa bazowa dla obiektów 3D.
///
/// Klasa reprezentuje ogólny obiekt 3D, który mo¿na przekszta³caæ (dziedziczy po TransformableObject).
/// Wymaga implementacji metod rysowania oraz przypisania tekstury.
class Shape3D : public virtual TransformableObject {
public:

    /// @brief Rysuje obiekt w przestrzeni 3D.
    ///
    /// Funkcja musi zostaæ zaimplementowana przez klasy pochodne.
    /// @param view Macierz widoku (np. kamery).
    virtual void draw(const glm::mat4& view) = 0;

    /// @brief Ustawia teksturê dla obiektu.
    ///
    /// Funkcja musi zostaæ zaimplementowana przez klasy pochodne.
    /// @param texture Identyfikator tekstury OpenGL.
    virtual void setTexture(GLuint texture) = 0;

    /// @brief Wirtualny destruktor.
    virtual ~Shape3D() = default;
};
