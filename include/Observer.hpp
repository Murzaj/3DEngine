#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "TransformableObject.hpp"

/// @brief Obserwator w scenie 3D.
///
/// Klasa reprezentuje kamer� lub obiekt obserwuj�cy scen� 3D.
/// Pozwala ustawi� transformacj� macierzy widoku za pomoc� funkcji `lookAt`.
class Observer : public TransformableObject {
public:

    /// @brief Konstruktor tworz�cy obserwatora z dan� pozycj�, celem i wektorem "g�ry".
    ///
    /// Inicjalizuje macierz widoku za pomoc� funkcji `glm::lookAt`.
    /// @param pos Pozycja obserwatora w przestrzeni.
    /// @param target Punkt, na kt�ry obserwator patrzy.
    /// @param up Kierunek "g�ry" (domy�lnie (0,1,0)).
    Observer(const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f))
        : TransformableObject(glm::lookAt(pos, target, up))
    {
    }

    /// @brief Ustawia now� macierz widoku na podstawie pozycji, celu i wektora g�ry.
    ///
    /// Aktualizuje transformacj� obiektu za pomoc� `glm::lookAt`.
    /// @param pos Nowa pozycja obserwatora.
    /// @param target Nowy punkt docelowy, na kt�ry patrzy obserwator.
    /// @param up Nowy kierunek "g�ry" (domy�lnie (0,1,0)).
    void lookAt(const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f)) {
        setTransform(glm::lookAt(pos, target, up));
    }

};
