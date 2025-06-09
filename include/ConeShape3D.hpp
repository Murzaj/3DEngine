#pragma once 

#include "PrimitiveShape3D.hpp"
#include <GL/glut.h>

/// @brief Reprezentuje sto�ek 3D jako prymityw graficzny.
///
/// Umo�liwia renderowanie kolorowego sto�ka w przestrzeni 3D
/// z okre�lon� podstaw�, wysoko�ci� oraz poziomem szczeg�owo�ci.
class ConeShape3D : public PrimitiveShape3D {
protected:
    double base;    ///< Promie� podstawy sto�ka.
    double height;  ///< Wysoko�� sto�ka.
    unsigned slices; ///< Liczba podzia��w w poziomie (wok� osi).
    unsigned stacks; ///< Liczba podzia��w w pionie.

    /// @brief Rysuje sto�ek za pomoc� GLUT.
    ///
    /// Funkcja wywo�ywana wewn�trznie przez `draw()` z klasy bazowej.
    virtual void primitiveDrawingFunc() override {
        glutSolidCone(base, height, slices, stacks); // Przywr�cono oryginalne rysowanie sto�ka
    }

public:
    /// @brief Konstruktor tworz�cy sto�ek z okre�lonymi parametrami.
    /// @param color Kolor sto�ka.
    /// @param base Promie� podstawy sto�ka.
    /// @param height Wysoko�� sto�ka.
    /// @param slices Liczba podzia��w wok� osi (segment�w poziomych).
    /// @param stacks Liczba warstw wzd�u� wysoko�ci (segment�w pionowych).
    ConeShape3D(const glm::vec3& color, double base, double height, unsigned slices, unsigned stacks) :
        PrimitiveShape3D(color),
        base(base),
        height(height),
        slices(slices),
        stacks(stacks)
    {
    }
};
