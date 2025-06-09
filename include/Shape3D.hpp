#pragma once

#include <GL/glew.h> 
#include <glm/glm.hpp>
#include "TransformableObject.hpp" 

/// @brief Abstrakcyjna klasa bazowa dla obiekt�w 3D.
///
/// Klasa reprezentuje og�lny obiekt 3D, kt�ry mo�na przekszta�ca� (dziedziczy po TransformableObject).
/// Wymaga implementacji metod rysowania oraz przypisania tekstury.
class Shape3D : public virtual TransformableObject {
public:

    /// @brief Rysuje obiekt w przestrzeni 3D.
    ///
    /// Funkcja musi zosta� zaimplementowana przez klasy pochodne.
    /// @param view Macierz widoku (np. kamery).
    virtual void draw(const glm::mat4& view) = 0;

    /// @brief Ustawia tekstur� dla obiektu.
    ///
    /// Funkcja musi zosta� zaimplementowana przez klasy pochodne.
    /// @param texture Identyfikator tekstury OpenGL.
    virtual void setTexture(GLuint texture) = 0;

    /// @brief Wirtualny destruktor.
    virtual ~Shape3D() = default;
};
