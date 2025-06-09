#pragma once 

#include <glm/glm.hpp>        
#include <glm/gtc/matrix_transform.hpp> 
#include "game/GameObject.hpp" 

/// @brief Klasa bazowa dla obiektów posiadaj¹cych transformacje w przestrzeni 3D.
/// 
/// Dziedziczy wirtualnie po GameObject, umo¿liwia operacje na macierzy transformacji,
/// takie jak przesuniêcie, obrót, skalowanie oraz reset do macierzy jednostkowej.
class TransformableObject : public virtual GameObject {
protected:
    glm::mat4 transform; ///< Macierz transformacji obiektu.

public:
    /// @brief Konstruktor z inicjalizacj¹ macierzy transformacji.
    /// @param initialTransform Macierz pocz¹tkowej transformacji.
    TransformableObject(const glm::mat4& initialTransform);

    /// @brief Konstruktor domyœlny, ustawia macierz transformacji na jednostkow¹.
    TransformableObject();

    /// @brief Domyœlny destruktor.
    virtual ~TransformableObject() = default;

    /// @brief Resetuje macierz transformacji do macierzy jednostkowej.
    void resetIdentity();

    /// @brief Przesuwa obiekt o wektor \p vec.
    /// @param vec Wektor przesuniêcia.
    void translate(const glm::vec3& vec);

    /// @brief Obraca obiekt o k¹t \p angleRadians wokó³ osi \p axis.
    /// @param angleRadians K¹t obrotu w radianach.
    /// @param axis Oœ obrotu jako wektor 3D.
    void rotate(float angleRadians, const glm::vec3& axis);

    /// @brief Skaluje obiekt wed³ug wektora \p scale.
    /// @param scale Wektor skalowania.
    void scale(const glm::vec3& scale);

    /// @brief Zwraca aktualn¹ macierz transformacji.
    /// @return Macierz 4x4 transformacji obiektu.
    glm::mat4 getTransform() const;

    /// @brief Ustawia now¹ macierz transformacji.
    /// @param newTransform Nowa macierz 4x4.
    void setTransform(const glm::mat4& newTransform);

    /// @brief Zwraca pozycjê obiektu wyodrêbnion¹ z macierzy transformacji.
    /// @return Wektor pozycji 3D.
    glm::vec3 getPositionFromTransform() const;

    /// @brief Ustawia pozycjê w macierzy transformacji.
    /// @param pos Nowa pozycja jako wektor 3D.
    void setPositionInTransform(const glm::vec3& pos);
};
