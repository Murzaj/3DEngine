#pragma once

#include "PrimitiveShape3D.hpp"
#include <GL/glut.h>

/// @brief Reprezentuje szeœcian 3D jako prymitywny kszta³t do renderowania.
///
/// Klasa umo¿liwia tworzenie i rysowanie kolorowego szeœcianu w przestrzeni 3D
/// z wykorzystaniem funkcji `glutSolidCube` z biblioteki GLUT.
class CubeShape3D : public PrimitiveShape3D {
protected:
    double size; ///< Rozmiar (d³ugoœæ krawêdzi) szeœcianu.

    /// @brief Funkcja rysuj¹ca szeœcian przy u¿yciu GLUT.
    ///
    /// Wywo³ywana przez metodê `draw()` z klasy bazowej.
    virtual void primitiveDrawingFunc() override {
        glutSolidCube(size);
    }

public:
    /// @brief Konstruktor klasy `CubeShape3D`.
    ///
    /// Tworzy szeœcian o okreœlonym kolorze i rozmiarze.
    /// @param color Kolor szeœcianu (RGB).
    /// @param size D³ugoœæ krawêdzi szeœcianu.
    CubeShape3D(const glm::vec3& color, double size) :
        PrimitiveShape3D(color),
        size(size) {
    }
};
