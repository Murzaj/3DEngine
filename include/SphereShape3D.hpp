#pragma once

#include "PrimitiveShape3D.hpp"
#include <GL/glut.h> 

/// @brief Klasa reprezentuj¹ca trójwymiarow¹ sferê jako kszta³t prymitywny.
/// 
/// Dziedziczy po PrimitiveShape3D i implementuje rysowanie sfery za pomoc¹ GLUT.
class SphereShape3D : public PrimitiveShape3D {
protected:
    double radius;   ///< Promieñ sfery.
    unsigned slices; ///< Liczba podzia³ów (plaszczyzn) wzd³u¿ osi poziomej.
    unsigned stacks; ///< Liczba podzia³ów (plaszczyzn) wzd³u¿ osi pionowej.

    /// @brief Metoda rysuj¹ca sferê za pomoc¹ funkcji GLUT.
    ///
    /// Wywo³ywana podczas renderowania obiektu, rysuje pe³n¹ bry³ê sfery.
    virtual void primitiveDrawingFunc() override {
        glutSolidSphere(radius, slices, stacks);
    }
public:
    /// @brief Konstruktor klasy SphereShape3D.
    /// @param color Kolor sfery (glm::vec3).
    /// @param radius Promieñ sfery.
    /// @param slices Liczba podzia³ów na plaszczyzny poziome.
    /// @param stacks Liczba podzia³ów na plaszczyzny pionowe.
    SphereShape3D(const glm::vec3& color, double radius, unsigned slices, unsigned stacks) :
        PrimitiveShape3D(color),
        radius(radius),
        slices(slices),
        stacks(stacks)
    {
    }
};
