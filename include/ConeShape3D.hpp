#pragma once 

#include "PrimitiveShape3D.hpp"
#include <GL/glut.h>

/// @brief Reprezentuje sto¿ek 3D jako prymityw graficzny.
///
/// Umo¿liwia renderowanie kolorowego sto¿ka w przestrzeni 3D
/// z okreœlon¹ podstaw¹, wysokoœci¹ oraz poziomem szczegó³owoœci.
class ConeShape3D : public PrimitiveShape3D {
protected:
    double base;    ///< Promieñ podstawy sto¿ka.
    double height;  ///< Wysokoœæ sto¿ka.
    unsigned slices; ///< Liczba podzia³ów w poziomie (wokó³ osi).
    unsigned stacks; ///< Liczba podzia³ów w pionie.

    /// @brief Rysuje sto¿ek za pomoc¹ GLUT.
    ///
    /// Funkcja wywo³ywana wewnêtrznie przez `draw()` z klasy bazowej.
    virtual void primitiveDrawingFunc() override {
        glutSolidCone(base, height, slices, stacks); // Przywrócono oryginalne rysowanie sto¿ka
    }

public:
    /// @brief Konstruktor tworz¹cy sto¿ek z okreœlonymi parametrami.
    /// @param color Kolor sto¿ka.
    /// @param base Promieñ podstawy sto¿ka.
    /// @param height Wysokoœæ sto¿ka.
    /// @param slices Liczba podzia³ów wokó³ osi (segmentów poziomych).
    /// @param stacks Liczba warstw wzd³u¿ wysokoœci (segmentów pionowych).
    ConeShape3D(const glm::vec3& color, double base, double height, unsigned slices, unsigned stacks) :
        PrimitiveShape3D(color),
        base(base),
        height(height),
        slices(slices),
        stacks(stacks)
    {
    }
};
