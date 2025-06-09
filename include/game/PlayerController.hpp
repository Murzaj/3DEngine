#pragma once 

#include <glm/glm.hpp>
#include "UpdatableObject.hpp"
#include "SphereShape3D.hpp" 
#include "InputMap.hpp"
#include "Initializer.hpp"
#include "TransformableObject.hpp" 

/// @brief Klasa kontroluj�ca ruch i zachowanie gracza.
///
/// Odpowiada za obs�ug� wej�cia gracza, detekcj� kolizji z pod�o�em,
/// fizyk� skoku oraz ograniczenie poruszania si� w poziomie.
/// Przechowuje r�wnie� referencj� do kszta�tu gracza.
class PlayerController : public UpdatableObject {
public:

    /// @brief Konstruktor kontrolera gracza.
    /// @param shape Wska�nik na obiekt 3D reprezentuj�cy gracza.
    /// @param radius Promie� gracza (do kolizji i fizyki).
    PlayerController(Shape3D* shape, float radius);

    /// @brief Inicjalizuje kontroler w kontek�cie silnika.
    /// @param initializer Obiekt dostarczaj�cy zale�no�ci i zasoby.
    /// @return true je�li inicjalizacja powiod�a si�.
    bool init(Initializer* initializer) override;

    /// @brief Aktualizuje pozycj� i logik� ruchu gracza.
    /// @param deltaMs Czas delta w milisekundach.
    /// @param input Dane wej�ciowe (klawiatura/mysz).
    /// @param manager Wska�nik do silnika.
    void update(float deltaMs, const InputMap& input, EngineManager* manager) override;

    /// @brief Przesuwa gracza do przodu w osi Z.
    /// @param speed Pr�dko�� przesuwania.
    void moveForward(float speed);

    /// @brief Zwraca pozycj� Z gracza.
    float getZ() const;

    /// @brief Zwraca pe�n� pozycj� gracza jako wektor 3D.
    glm::vec3 getPosition() const;

    /// @brief Zwraca promie� gracza.
    float getRadius() const;

    /// @brief Zwraca wska�nik na kszta�t graficzny gracza.
    Shape3D* getShape() const;

    /// @brief Ustawia now� pozycj� gracza.
    /// @param pos Pozycja jako wektor 3D.
    void setPosition(const glm::vec3& pos);

    float minX = -5.0f;            ///< Lewa granica ruchu gracza w osi X.
    float maxX = 5.0f;             ///< Prawa granica ruchu gracza w osi X.

    float platformSurfaceY = -1.0f; ///< Wysoko�� powierzchni platformy (dla wykrycia l�dowania).

private:
    EngineManager* engineManager = nullptr; ///< Wska�nik do silnika gry.
    Shape3D* shape = nullptr;               ///< Wska�nik na kszta�t gracza.
    glm::vec3 position;                     ///< Aktualna pozycja gracza.
    float radius;                           ///< Promie� gracza.
    float sideSpeed = 5.0f;                 ///< Pr�dko�� ruchu w bok.
    float velocityY = 0.0f;                 ///< Pr�dko�� pionowa gracza (grawitacja/skok).
};
