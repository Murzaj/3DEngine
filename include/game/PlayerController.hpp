#pragma once 

#include <glm/glm.hpp>
#include "UpdatableObject.hpp"
#include "SphereShape3D.hpp" 
#include "InputMap.hpp"
#include "Initializer.hpp"
#include "TransformableObject.hpp" 

/// @brief Klasa kontroluj¹ca ruch i zachowanie gracza.
///
/// Odpowiada za obs³ugê wejœcia gracza, detekcjê kolizji z pod³o¿em,
/// fizykê skoku oraz ograniczenie poruszania siê w poziomie.
/// Przechowuje równie¿ referencjê do kszta³tu gracza.
class PlayerController : public UpdatableObject {
public:

    /// @brief Konstruktor kontrolera gracza.
    /// @param shape WskaŸnik na obiekt 3D reprezentuj¹cy gracza.
    /// @param radius Promieñ gracza (do kolizji i fizyki).
    PlayerController(Shape3D* shape, float radius);

    /// @brief Inicjalizuje kontroler w kontekœcie silnika.
    /// @param initializer Obiekt dostarczaj¹cy zale¿noœci i zasoby.
    /// @return true jeœli inicjalizacja powiod³a siê.
    bool init(Initializer* initializer) override;

    /// @brief Aktualizuje pozycjê i logikê ruchu gracza.
    /// @param deltaMs Czas delta w milisekundach.
    /// @param input Dane wejœciowe (klawiatura/mysz).
    /// @param manager WskaŸnik do silnika.
    void update(float deltaMs, const InputMap& input, EngineManager* manager) override;

    /// @brief Przesuwa gracza do przodu w osi Z.
    /// @param speed Prêdkoœæ przesuwania.
    void moveForward(float speed);

    /// @brief Zwraca pozycjê Z gracza.
    float getZ() const;

    /// @brief Zwraca pe³n¹ pozycjê gracza jako wektor 3D.
    glm::vec3 getPosition() const;

    /// @brief Zwraca promieñ gracza.
    float getRadius() const;

    /// @brief Zwraca wskaŸnik na kszta³t graficzny gracza.
    Shape3D* getShape() const;

    /// @brief Ustawia now¹ pozycjê gracza.
    /// @param pos Pozycja jako wektor 3D.
    void setPosition(const glm::vec3& pos);

    float minX = -5.0f;            ///< Lewa granica ruchu gracza w osi X.
    float maxX = 5.0f;             ///< Prawa granica ruchu gracza w osi X.

    float platformSurfaceY = -1.0f; ///< Wysokoœæ powierzchni platformy (dla wykrycia l¹dowania).

private:
    EngineManager* engineManager = nullptr; ///< WskaŸnik do silnika gry.
    Shape3D* shape = nullptr;               ///< WskaŸnik na kszta³t gracza.
    glm::vec3 position;                     ///< Aktualna pozycja gracza.
    float radius;                           ///< Promieñ gracza.
    float sideSpeed = 5.0f;                 ///< Prêdkoœæ ruchu w bok.
    float velocityY = 0.0f;                 ///< Prêdkoœæ pionowa gracza (grawitacja/skok).
};
