#pragma once

#include "PrimitiveShape3D.hpp"
#include <GL/glut.h> 

/// @brief Klasa reprezentuj¹ca trójwymiarowy tor jako kszta³t prymitywny.
/// 
/// Dziedziczy po PrimitiveShape3D i implementuje rysowanie torusa za pomoc¹ GLUT.
class TorusShape3D : public PrimitiveShape3D {
protected:
    double innerRadius; ///< Promieñ wewnêtrzny torusa.
    double outerRadius; ///< Promieñ zewnêtrzny torusa.
    GLint sides;        ///< Liczba boków (segmentów) przekroju torusa.
    GLint rings;        ///< Liczba pierœcieni tworz¹cych torus.

    /// @brief Metoda rysuj¹ca torus za pomoc¹ funkcji GLUT.
    ///
    /// Wywo³ywana podczas renderowania obiektu, rysuje pe³n¹ bry³ê torusa.
    virtual void primitiveDrawingFunc() override {
        glutSolidTorus(innerRadius, outerRadius, sides, rings);
    }
public:
    /// @brief Konstruktor klasy TorusShape3D.
    /// @param color Kolor torusa (glm::vec3).
    /// @param innerRadius Promieñ wewnêtrzny torusa.
    /// @param outerRadius Promieñ zewnêtrzny torusa.
    /// @param sides Liczba boków przekroju torusa.
    /// @param rings Liczba pierœcieni torusa.
    TorusShape3D(const glm::vec3& color,
        double innerRadius,
        double outerRadius,
        GLint sides,
        GLint rings) :
        PrimitiveShape3D(color),
        innerRadius(innerRadius),
        outerRadius(outerRadius),
        sides(sides),
        rings(rings)
    {
    }
};
