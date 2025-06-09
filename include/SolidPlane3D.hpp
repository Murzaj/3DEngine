#ifndef SOLIDPLANE3D_HPP
#define SOLIDPLANE3D_HPP

#include "PrimitiveShape3D.hpp"
#include <glm/glm.hpp>

/// @brief Klasa reprezentuj¹ca p³aski, kolorowy prostok¹t 3D.
///
/// SolidPlane3D to prymitywna p³aszczyzna (kwadrat) renderowana w przestrzeni 3D.
/// Klasa dziedziczy po PrimitiveShape3D i implementuje metodê rysowania geometrycznego prymitywu.
class SolidPlane3D : public PrimitiveShape3D {
public:
    /// @brief Konstruktor tworz¹cy p³aszczyznê o zadanym rozmiarze i kolorze.
    /// @param halfSize Po³owa d³ugoœci boku kwadratu (pe³ny bok = 2 * halfSize).
    /// @param color Kolor p³aszczyzny.
    SolidPlane3D(float halfSize, const glm::vec3& color);

private:
    float halfSize;      ///< Po³owa d³ugoœci boku kwadratu.
    glm::vec3 color;     ///< Kolor p³aszczyzny.

    /// @brief Implementacja funkcji rysuj¹cej p³aszczyznê.
    ///
    /// Funkcja wywo³ywana przez draw(), wykonuje w³aœciwe polecenia OpenGL do narysowania prymitywu.
    virtual void primitiveDrawingFunc() override;
};

#endif
