#pragma once

#include "PrimitiveShape3D.hpp"
#include <GL/glut.h>

/// @brief Reprezentuje sze�cian 3D jako prymitywny kszta�t do renderowania.
///
/// Klasa umo�liwia tworzenie i rysowanie kolorowego sze�cianu w przestrzeni 3D
/// z wykorzystaniem funkcji `glutSolidCube` z biblioteki GLUT.
class CubeShape3D : public PrimitiveShape3D {
protected:
    double size; ///< Rozmiar (d�ugo�� kraw�dzi) sze�cianu.

    /// @brief Funkcja rysuj�ca sze�cian przy u�yciu GLUT.
    ///
    /// Wywo�ywana przez metod� `draw()` z klasy bazowej.
    virtual void primitiveDrawingFunc() override {
        glutSolidCube(size);
    }

public:
    /// @brief Konstruktor klasy `CubeShape3D`.
    ///
    /// Tworzy sze�cian o okre�lonym kolorze i rozmiarze.
    /// @param color Kolor sze�cianu (RGB).
    /// @param size D�ugo�� kraw�dzi sze�cianu.
    CubeShape3D(const glm::vec3& color, double size) :
        PrimitiveShape3D(color),
        size(size) {
    }
};
