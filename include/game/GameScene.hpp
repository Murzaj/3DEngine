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

/// @brief Reprezentuje g³ówn¹ scenê gry 3D.
///
/// Zawiera logikê gry, zarz¹dza graczem, przeszkodami (kolcami),
/// platform¹ oraz œcianami. Odpowiada za aktualizacjê, rysowanie,
/// wykrywanie kolizji i generowanie nowych przeszkód.
class GameScene : public UpdatableObject {
public:

    /// @brief Konstruktor domyœlny sceny gry.
    GameScene();

    /// @brief Konstruktor inicjalizuj¹cy scenê z graczem i tekstur¹ kolców.
    /// @param playerShape WskaŸnik na kszta³t gracza.
    /// @param playerRadius Promieñ gracza.
    /// @param spikeTexture Tekstura kolców.
    GameScene(Shape3D* playerShape, float playerRadius, GLuint spikeTexture);

    /// @brief Destruktor zwalniaj¹cy zasoby sceny.
    virtual ~GameScene();

    /// @brief Inicjalizuje scenê gry.
    /// @param initializer Obiekt inicjalizacyjny z dostêpem do silnika.
    /// @return true jeœli inicjalizacja siê powiod³a.
    bool init(Initializer* initializer) override;

    /// @brief Aktualizuje stan sceny gry.
    /// @param deltaMs Czas delta w milisekundach.
    /// @param input Mapa wejœciowa (klawiatura/mysz).
    /// @param manager Mened¿er silnika.
    void update(float deltaMs, const InputMap& input, EngineManager* manager) override;

    /// @brief Zwraca aktualny wynik gracza.
    /// @return Wynik jako liczba ca³kowita.
    int getScore() const;

    /// @brief Ustawia aktywnoœæ widoku wyboru mapy.
    /// @param active true jeœli widok mapy ma byæ aktywny.
    void setActiveMapSelection(bool active);

    /// @brief Sprawdza, czy aktywny jest widok wyboru mapy.
    /// @return true jeœli aktywny.
    bool isActiveMapSelection() const;

private:
    EngineManager* engineManager = nullptr; ///< WskaŸnik na mened¿era silnika.
    PlayerController playerController;      ///< Kontroler gracza.
    GLuint spikeTexture;                    ///< Tekstura u¿ywana dla kolców.
    GLuint platformTexture;                 ///< Tekstura platformy (jeœli u¿ywana).

    std::vector<Spike*> spikes;             ///< Lista aktywnych kolców na scenie.
    float forwardSpeed;                     ///< Aktualna prêdkoœæ przesuwania do przodu.
    float speedIncrease;                    ///< Wspó³czynnik przyspieszenia.
    float nextSpikeZ;                       ///< Pozycja Z do kolejnego spawnu kolca.
    std::default_random_engine rng;         ///< Generator pseudolosowy.

    std::uniform_real_distribution<float> distributionX;        ///< Rozrzut pozycji kolców w osi X.
    std::uniform_real_distribution<float> distributionZOffset;  ///< Rozrzut odstêpu miêdzy kolcami.
    bool distributionX_initialized = false;                     ///< Czy rozk³ad X zosta³ zainicjalizowany.
    bool distributionZOffset_initialized = false;               ///< Czy rozk³ad Z zosta³ zainicjalizowany.

    PrimitiveShape3D* platform = nullptr;   ///< Platforma, po której porusza siê gracz.
    float platformWidth = 10.0f;            ///< Szerokoœæ platformy.
    float platformLength = 1000.0f;         ///< D³ugoœæ segmentu platformy.
    float platformY = -1.0f;                ///< Wysokoœæ platformy (Y).

    CubeShape3D* leftWall = nullptr;        ///< Lewa œciana ograniczaj¹ca scenê.
    CubeShape3D* rightWall = nullptr;       ///< Prawa œciana ograniczaj¹ca scenê.
    float wallHeight = 0.5f;                ///< Wysokoœæ œcian bocznych.
    float wallThickness = 0.2f;             ///< Gruboœæ œcian bocznych.

    float score;                            ///< Wynik gracza.
    bool playerDead = false;                ///< Flaga stanu gracza (¿yje/nie ¿yje).

    /// @brief Inicjalizuje rozk³ady losowe, jeœli jeszcze nie s¹ gotowe.
    void initializeDistributionsIfNeeded();

    /// @brief Generuje nowy kolec na scenie.
    /// @param initializer Obiekt inicjalizacyjny.
    void spawnSpike(Initializer* initializer);

    /// @brief Sprawdza kolizje miêdzy graczem a kolcami.
    /// @param manager Mened¿er silnika.
    void checkCollisions(EngineManager* manager);

    /// @brief Usuwa kolce, które znajduj¹ siê za graczem.
    void cleanupSpikes();

    /// @brief Zarz¹dza tworzeniem nowych kolców w miarê postêpu gry.
    /// @param initializer Obiekt inicjalizacyjny.
    void manageSpawns(Initializer* initializer);

    /// @brief Resetuje stan gry do wartoœci pocz¹tkowych.
    void resetGame();
};
