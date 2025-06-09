#pragma once

#include <GL/glew.h>
#include "ConeShape3D.hpp"

/// @brief Reprezentuje obiekt kolca w grze.
///
/// Klasa dziedziczy po `ConeShape3D` i definiuje sta³e wymiary geometryczne.
/// Kolce mog¹ byæ u¿ywane jako przeszkody generowane w trakcie gry.
class Spike : public ConeShape3D {
public:

    /// @brief Konstruktor tworz¹cy kolec z okreœlon¹ tekstur¹.
    /// @param texture Tekstura przypisana do kolca.
    explicit Spike(GLuint texture);

    /// @brief Zwraca promieñ podstawy kolca.
    /// @return Promieñ podstawy jako liczba zmiennoprzecinkowa.
    float getRadius() const {
        return baseRadius;
    }

    /// @brief Zwraca wysokoœæ kolca.
    /// @return Wysokoœæ kolca jako liczba zmiennoprzecinkowa.
    float getHeight() const {
        return height;
    }

    /// @brief Statyczna sta³a okreœlaj¹ca promieñ podstawy kolca.
    static const float baseRadius;

    /// @brief Statyczna sta³a okreœlaj¹ca wysokoœæ kolca.
    static const float height;
};
