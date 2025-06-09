#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "TransformableObject.hpp"

/// @brief Obserwator w scenie 3D.
///
/// Klasa reprezentuje kamerê lub obiekt obserwuj¹cy scenê 3D.
/// Pozwala ustawiæ transformacjê macierzy widoku za pomoc¹ funkcji `lookAt`.
class Observer : public TransformableObject {
public:

    /// @brief Konstruktor tworz¹cy obserwatora z dan¹ pozycj¹, celem i wektorem "góry".
    ///
    /// Inicjalizuje macierz widoku za pomoc¹ funkcji `glm::lookAt`.
    /// @param pos Pozycja obserwatora w przestrzeni.
    /// @param target Punkt, na który obserwator patrzy.
    /// @param up Kierunek "góry" (domyœlnie (0,1,0)).
    Observer(const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f))
        : TransformableObject(glm::lookAt(pos, target, up))
    {
    }

    /// @brief Ustawia now¹ macierz widoku na podstawie pozycji, celu i wektora góry.
    ///
    /// Aktualizuje transformacjê obiektu za pomoc¹ `glm::lookAt`.
    /// @param pos Nowa pozycja obserwatora.
    /// @param target Nowy punkt docelowy, na który patrzy obserwator.
    /// @param up Nowy kierunek "góry" (domyœlnie (0,1,0)).
    void lookAt(const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f)) {
        setTransform(glm::lookAt(pos, target, up));
    }

};
