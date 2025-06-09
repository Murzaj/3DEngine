#pragma once 

#include <glm/glm.hpp>
#include "Initializer.hpp" 

class Shape3D;

/// @brief Bazowa klasa dla wszystkich obiektów gry w przestrzeni 3D.
///
/// Umo¿liwia przypisanie kszta³tu graficznego (`Shape3D`) oraz zarz¹dzanie pozycj¹ obiektu.
/// Klasa mo¿e byæ rozszerzana przez inne klasy reprezentuj¹ce konkretne elementy gry.
class GameObject {
private:
    Shape3D* shape = nullptr; ///< WskaŸnik na kszta³t graficzny przypisany do obiektu.
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f); ///< Aktualna pozycja obiektu w przestrzeni 3D.

public:

    /// @brief Wirtualny destruktor.
    virtual ~GameObject() = default;

    /// @brief Inicjalizuje obiekt.
    /// @param initializer Obiekt dostarczaj¹cy zale¿noœci i dane inicjalizacyjne.
    /// @return true jeœli inicjalizacja powiod³a siê (domyœlnie zawsze true).
    virtual bool init(Initializer* initializer) { return true; }

    /// @brief Ustawia kszta³t (`Shape3D`) przypisany do obiektu.
    /// @param newShape WskaŸnik na nowy kszta³t.
    void setShape(Shape3D* newShape) {
        shape = newShape;
    }

    /// @brief Zwraca aktualnie przypisany kszta³t graficzny.
    /// @return WskaŸnik na `Shape3D`.
    Shape3D* getShape() const {
        return shape;
    }

    /// @brief Ustawia pozycjê obiektu.
    /// @param x Wspó³rzêdna X.
    /// @param y Wspó³rzêdna Y.
    /// @param z Wspó³rzêdna Z.
    virtual void setPosition(float x, float y, float z) {
        position = glm::vec3(x, y, z);
    }

    /// @brief Ustawia pozycjê obiektu.
    /// @param pos Nowa pozycja jako wektor 3D.
    virtual void setPosition(const glm::vec3& pos) {
        position = pos;
    }

    /// @brief Zwraca aktualn¹ pozycjê obiektu.
    /// @return Wektor 3D reprezentuj¹cy pozycjê.
    glm::vec3 getPosition() const {
        return position;
    }

    /// @brief Przesuwa obiekt o zadany wektor.
    /// @param dx Przesuniêcie w osi X.
    /// @param dy Przesuniêcie w osi Y.
    /// @param dz Przesuniêcie w osi Z.
    void move(float dx, float dy, float dz) {
        position += glm::vec3(dx, dy, dz);
    }
};
