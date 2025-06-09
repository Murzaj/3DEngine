#pragma once 

#include <glm/glm.hpp>
#include "Initializer.hpp" 

class Shape3D;

/// @brief Bazowa klasa dla wszystkich obiekt�w gry w przestrzeni 3D.
///
/// Umo�liwia przypisanie kszta�tu graficznego (`Shape3D`) oraz zarz�dzanie pozycj� obiektu.
/// Klasa mo�e by� rozszerzana przez inne klasy reprezentuj�ce konkretne elementy gry.
class GameObject {
private:
    Shape3D* shape = nullptr; ///< Wska�nik na kszta�t graficzny przypisany do obiektu.
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f); ///< Aktualna pozycja obiektu w przestrzeni 3D.

public:

    /// @brief Wirtualny destruktor.
    virtual ~GameObject() = default;

    /// @brief Inicjalizuje obiekt.
    /// @param initializer Obiekt dostarczaj�cy zale�no�ci i dane inicjalizacyjne.
    /// @return true je�li inicjalizacja powiod�a si� (domy�lnie zawsze true).
    virtual bool init(Initializer* initializer) { return true; }

    /// @brief Ustawia kszta�t (`Shape3D`) przypisany do obiektu.
    /// @param newShape Wska�nik na nowy kszta�t.
    void setShape(Shape3D* newShape) {
        shape = newShape;
    }

    /// @brief Zwraca aktualnie przypisany kszta�t graficzny.
    /// @return Wska�nik na `Shape3D`.
    Shape3D* getShape() const {
        return shape;
    }

    /// @brief Ustawia pozycj� obiektu.
    /// @param x Wsp�rz�dna X.
    /// @param y Wsp�rz�dna Y.
    /// @param z Wsp�rz�dna Z.
    virtual void setPosition(float x, float y, float z) {
        position = glm::vec3(x, y, z);
    }

    /// @brief Ustawia pozycj� obiektu.
    /// @param pos Nowa pozycja jako wektor 3D.
    virtual void setPosition(const glm::vec3& pos) {
        position = pos;
    }

    /// @brief Zwraca aktualn� pozycj� obiektu.
    /// @return Wektor 3D reprezentuj�cy pozycj�.
    glm::vec3 getPosition() const {
        return position;
    }

    /// @brief Przesuwa obiekt o zadany wektor.
    /// @param dx Przesuni�cie w osi X.
    /// @param dy Przesuni�cie w osi Y.
    /// @param dz Przesuni�cie w osi Z.
    void move(float dx, float dy, float dz) {
        position += glm::vec3(dx, dy, dz);
    }
};
