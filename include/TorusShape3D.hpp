#pragma once

#include "PrimitiveShape3D.hpp"
#include <GL/glut.h> 

/// @brief Klasa reprezentuj�ca tr�jwymiarowy tor jako kszta�t prymitywny.
/// 
/// Dziedziczy po PrimitiveShape3D i implementuje rysowanie torusa za pomoc� GLUT.
class TorusShape3D : public PrimitiveShape3D {
protected:
    double innerRadius; ///< Promie� wewn�trzny torusa.
    double outerRadius; ///< Promie� zewn�trzny torusa.
    GLint sides;        ///< Liczba bok�w (segment�w) przekroju torusa.
    GLint rings;        ///< Liczba pier�cieni tworz�cych torus.

    /// @brief Metoda rysuj�ca torus za pomoc� funkcji GLUT.
    ///
    /// Wywo�ywana podczas renderowania obiektu, rysuje pe�n� bry�� torusa.
    virtual void primitiveDrawingFunc() override {
        glutSolidTorus(innerRadius, outerRadius, sides, rings);
    }
public:
    /// @brief Konstruktor klasy TorusShape3D.
    /// @param color Kolor torusa (glm::vec3).
    /// @param innerRadius Promie� wewn�trzny torusa.
    /// @param outerRadius Promie� zewn�trzny torusa.
    /// @param sides Liczba bok�w przekroju torusa.
    /// @param rings Liczba pier�cieni torusa.
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
