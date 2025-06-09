#pragma once 

#include <vector>
#include <random>
#include <GL/glew.h>

#include "UpdatableObject.hpp"
#include "game/PlayerController.hpp"
#include "PrimitiveShape3D.hpp"
#include "TexturedPlane3D.hpp"
#include "game/ColoredPlane3D.hpp"

class Spike;
class TexturedPlane3D;
class CubeShape3D;

/// @brief Reprezentuje g��wn� scen� gry 3D.
///
/// Zawiera logik� gry, zarz�dza graczem, przeszkodami (kolcami),
/// platform� oraz �cianami. Odpowiada za aktualizacj�, rysowanie,
/// wykrywanie kolizji i generowanie nowych przeszk�d.
class GameScene : public UpdatableObject {
public:

    /// @brief Konstruktor domy�lny sceny gry.
    GameScene();

    /// @brief Konstruktor inicjalizuj�cy scen� z graczem i tekstur� kolc�w.
    /// @param playerShape Wska�nik na kszta�t gracza.
    /// @param playerRadius Promie� gracza.
    /// @param spikeTexture Tekstura kolc�w.
    GameScene(Shape3D* playerShape, float playerRadius, GLuint spikeTexture);

    /// @brief Destruktor zwalniaj�cy zasoby sceny.
    virtual ~GameScene();

    /// @brief Inicjalizuje scen� gry.
    /// @param initializer Obiekt inicjalizacyjny z dost�pem do silnika.
    /// @return true je�li inicjalizacja si� powiod�a.
    bool init(Initializer* initializer) override;

    /// @brief Aktualizuje stan sceny gry.
    /// @param deltaMs Czas delta w milisekundach.
    /// @param input Mapa wej�ciowa (klawiatura/mysz).
    /// @param manager Mened�er silnika.
    void update(float deltaMs, const InputMap& input, EngineManager* manager) override;

    /// @brief Zwraca aktualny wynik gracza.
    /// @return Wynik jako liczba ca�kowita.
    int getScore() const;

    /// @brief Ustawia aktywno�� widoku wyboru mapy.
    /// @param active true je�li widok mapy ma by� aktywny.
    void setActiveMapSelection(bool active);

    /// @brief Sprawdza, czy aktywny jest widok wyboru mapy.
    /// @return true je�li aktywny.
    bool isActiveMapSelection() const;

private:
    EngineManager* engineManager = nullptr; ///< Wska�nik na mened�era silnika.
    PlayerController playerController;      ///< Kontroler gracza.
    GLuint spikeTexture;                    ///< Tekstura u�ywana dla kolc�w.
    GLuint platformTexture;                 ///< Tekstura platformy (je�li u�ywana).

    std::vector<Spike*> spikes;             ///< Lista aktywnych kolc�w na scenie.
    float forwardSpeed;                     ///< Aktualna pr�dko�� przesuwania do przodu.
    float speedIncrease;                    ///< Wsp�czynnik przyspieszenia.
    float nextSpikeZ;                       ///< Pozycja Z do kolejnego spawnu kolca.
    std::default_random_engine rng;         ///< Generator pseudolosowy.

    std::uniform_real_distribution<float> distributionX;        ///< Rozrzut pozycji kolc�w w osi X.
    std::uniform_real_distribution<float> distributionZOffset;  ///< Rozrzut odst�pu mi�dzy kolcami.
    bool distributionX_initialized = false;                     ///< Czy rozk�ad X zosta� zainicjalizowany.
    bool distributionZOffset_initialized = false;               ///< Czy rozk�ad Z zosta� zainicjalizowany.

    PrimitiveShape3D* platform = nullptr;   ///< Platforma, po kt�rej porusza si� gracz.
    float platformWidth = 10.0f;            ///< Szeroko�� platformy.
    float platformLength = 1000.0f;         ///< D�ugo�� segmentu platformy.
    float platformY = -1.0f;                ///< Wysoko�� platformy (Y).

    CubeShape3D* leftWall = nullptr;        ///< Lewa �ciana ograniczaj�ca scen�.
    CubeShape3D* rightWall = nullptr;       ///< Prawa �ciana ograniczaj�ca scen�.
    float wallHeight = 0.5f;                ///< Wysoko�� �cian bocznych.
    float wallThickness = 0.2f;             ///< Grubo�� �cian bocznych.

    float score;                            ///< Wynik gracza.
    bool playerDead = false;                ///< Flaga stanu gracza (�yje/nie �yje).

    /// @brief Inicjalizuje rozk�ady losowe, je�li jeszcze nie s� gotowe.
    void initializeDistributionsIfNeeded();

    /// @brief Generuje nowy kolec na scenie.
    /// @param initializer Obiekt inicjalizacyjny.
    void spawnSpike(Initializer* initializer);

    /// @brief Sprawdza kolizje mi�dzy graczem a kolcami.
    /// @param manager Mened�er silnika.
    void checkCollisions(EngineManager* manager);

    /// @brief Usuwa kolce, kt�re znajduj� si� za graczem.
    void cleanupSpikes();

    /// @brief Zarz�dza tworzeniem nowych kolc�w w miar� post�pu gry.
    /// @param initializer Obiekt inicjalizacyjny.
    void manageSpawns(Initializer* initializer);

    /// @brief Resetuje stan gry do warto�ci pocz�tkowych.
    void resetGame();
};
