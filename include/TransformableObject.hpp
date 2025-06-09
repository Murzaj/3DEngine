#pragma once 

#include <glm/glm.hpp>        
#include <glm/gtc/matrix_transform.hpp> 
#include "game/GameObject.hpp" 

/// @brief Klasa bazowa dla obiekt�w posiadaj�cych transformacje w przestrzeni 3D.
/// 
/// Dziedziczy wirtualnie po GameObject, umo�liwia operacje na macierzy transformacji,
/// takie jak przesuni�cie, obr�t, skalowanie oraz reset do macierzy jednostkowej.
class TransformableObject : public virtual GameObject {
protected:
    glm::mat4 transform; ///< Macierz transformacji obiektu.

public:
    /// @brief Konstruktor z inicjalizacj� macierzy transformacji.
    /// @param initialTransform Macierz pocz�tkowej transformacji.
    TransformableObject(const glm::mat4& initialTransform);

    /// @brief Konstruktor domy�lny, ustawia macierz transformacji na jednostkow�.
    TransformableObject();

    /// @brief Domy�lny destruktor.
    virtual ~TransformableObject() = default;

    /// @brief Resetuje macierz transformacji do macierzy jednostkowej.
    void resetIdentity();

    /// @brief Przesuwa obiekt o wektor \p vec.
    /// @param vec Wektor przesuni�cia.
    void translate(const glm::vec3& vec);

    /// @brief Obraca obiekt o k�t \p angleRadians wok� osi \p axis.
    /// @param angleRadians K�t obrotu w radianach.
    /// @param axis O� obrotu jako wektor 3D.
    void rotate(float angleRadians, const glm::vec3& axis);

    /// @brief Skaluje obiekt wed�ug wektora \p scale.
    /// @param scale Wektor skalowania.
    void scale(const glm::vec3& scale);

    /// @brief Zwraca aktualn� macierz transformacji.
    /// @return Macierz 4x4 transformacji obiektu.
    glm::mat4 getTransform() const;

    /// @brief Ustawia now� macierz transformacji.
    /// @param newTransform Nowa macierz 4x4.
    void setTransform(const glm::mat4& newTransform);

    /// @brief Zwraca pozycj� obiektu wyodr�bnion� z macierzy transformacji.
    /// @return Wektor pozycji 3D.
    glm::vec3 getPositionFromTransform() const;

    /// @brief Ustawia pozycj� w macierzy transformacji.
    /// @param pos Nowa pozycja jako wektor 3D.
    void setPositionInTransform(const glm::vec3& pos);
};
