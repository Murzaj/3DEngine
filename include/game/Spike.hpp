#pragma once

#include <GL/glew.h>
#include "ConeShape3D.hpp"

/// @brief Reprezentuje obiekt kolca w grze.
///
/// Klasa dziedziczy po `ConeShape3D` i definiuje sta�e wymiary geometryczne.
/// Kolce mog� by� u�ywane jako przeszkody generowane w trakcie gry.
class Spike : public ConeShape3D {
public:

    /// @brief Konstruktor tworz�cy kolec z okre�lon� tekstur�.
    /// @param texture Tekstura przypisana do kolca.
    explicit Spike(GLuint texture);

    /// @brief Zwraca promie� podstawy kolca.
    /// @return Promie� podstawy jako liczba zmiennoprzecinkowa.
    float getRadius() const {
        return baseRadius;
    }

    /// @brief Zwraca wysoko�� kolca.
    /// @return Wysoko�� kolca jako liczba zmiennoprzecinkowa.
    float getHeight() const {
        return height;
    }

    /// @brief Statyczna sta�a okre�laj�ca promie� podstawy kolca.
    static const float baseRadius;

    /// @brief Statyczna sta�a okre�laj�ca wysoko�� kolca.
    static const float height;
};
