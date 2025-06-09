#pragma once

#include "PrimitiveShape3D.hpp"
#include <GL/glut.h> 

/// @brief Klasa reprezentuj�ca tr�jwymiarow� sfer� jako kszta�t prymitywny.
/// 
/// Dziedziczy po PrimitiveShape3D i implementuje rysowanie sfery za pomoc� GLUT.
class SphereShape3D : public PrimitiveShape3D {
protected:
    double radius;   ///< Promie� sfery.
    unsigned slices; ///< Liczba podzia��w (plaszczyzn) wzd�u� osi poziomej.
    unsigned stacks; ///< Liczba podzia��w (plaszczyzn) wzd�u� osi pionowej.

    /// @brief Metoda rysuj�ca sfer� za pomoc� funkcji GLUT.
    ///
    /// Wywo�ywana podczas renderowania obiektu, rysuje pe�n� bry�� sfery.
    virtual void primitiveDrawingFunc() override {
        glutSolidSphere(radius, slices, stacks);
    }
public:
    /// @brief Konstruktor klasy SphereShape3D.
    /// @param color Kolor sfery (glm::vec3).
    /// @param radius Promie� sfery.
    /// @param slices Liczba podzia��w na plaszczyzny poziome.
    /// @param stacks Liczba podzia��w na plaszczyzny pionowe.
    SphereShape3D(const glm::vec3& color, double radius, unsigned slices, unsigned stacks) :
        PrimitiveShape3D(color),
        radius(radius),
        slices(slices),
        stacks(stacks)
    {
    }
};
