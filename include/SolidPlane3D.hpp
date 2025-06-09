#ifndef SOLIDPLANE3D_HPP
#define SOLIDPLANE3D_HPP

#include "PrimitiveShape3D.hpp"
#include <glm/glm.hpp>

/// @brief Klasa reprezentuj�ca p�aski, kolorowy prostok�t 3D.
///
/// SolidPlane3D to prymitywna p�aszczyzna (kwadrat) renderowana w przestrzeni 3D.
/// Klasa dziedziczy po PrimitiveShape3D i implementuje metod� rysowania geometrycznego prymitywu.
class SolidPlane3D : public PrimitiveShape3D {
public:
    /// @brief Konstruktor tworz�cy p�aszczyzn� o zadanym rozmiarze i kolorze.
    /// @param halfSize Po�owa d�ugo�ci boku kwadratu (pe�ny bok = 2 * halfSize).
    /// @param color Kolor p�aszczyzny.
    SolidPlane3D(float halfSize, const glm::vec3& color);

private:
    float halfSize;      ///< Po�owa d�ugo�ci boku kwadratu.
    glm::vec3 color;     ///< Kolor p�aszczyzny.

    /// @brief Implementacja funkcji rysuj�cej p�aszczyzn�.
    ///
    /// Funkcja wywo�ywana przez draw(), wykonuje w�a�ciwe polecenia OpenGL do narysowania prymitywu.
    virtual void primitiveDrawingFunc() override;
};

#endif
