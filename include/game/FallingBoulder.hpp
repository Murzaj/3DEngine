#pragma once
#include "UpdatableObject.hpp"
#include "Shape3D.hpp"
#include "game/Player.hpp"
#include <random>

/// @brief Reprezentuje spadaj¹cy g³az w œwiecie gry.
///
/// Klasa odpowiedzialna za tworzenie, rysowanie i aktualizacjê pozycji spadaj¹cych g³azów.
/// G³azy pojawiaj¹ siê losowo w zadanym obszarze i znikaj¹ po przekroczeniu okreœlonej wysokoœci.
class FallingBoulder : public UpdatableObject, public Shape3D {
protected:
    float speed;                                ///< Prêdkoœæ spadania g³azu.
    glm::vec3 pos;                               ///< Aktualna pozycja g³azu.
    glm::vec3 origin;                            ///< Punkt pocz¹tkowy rozrzutu.
    glm::vec3 spread;                            ///< Zakres rozrzutu pozycji.
    float size;                                  ///< Rozmiar g³azu.
    float deathY;                                ///< Pozycja Y, poni¿ej której g³az znika.
    Shape3D* boulderModel;                       ///< Model 3D reprezentuj¹cy g³az.
    Player* player;                              ///< WskaŸnik na gracza (do detekcji kolizji lub interakcji).

    std::random_device rd;                       ///< Urz¹dzenie losuj¹ce (dla RNG).
    std::uniform_real_distribution<float> xDistribution; ///< Rozrzut wspó³rzêdnej X.
    std::uniform_real_distribution<float> yDistribution; ///< Rozrzut wspó³rzêdnej Y.
    std::uniform_real_distribution<float> zDistribution; ///< Rozrzut wspó³rzêdnej Z.
    std::uniform_real_distribution<float> speedDistribution; ///< Rozrzut prêdkoœci.
    std::uniform_real_distribution<float> sizeDistribution;  ///< Rozrzut rozmiaru.
    std::mt19937 rng;                            ///< Generator liczb pseudolosowych.

public:

    /// @brief Tworzy nowy obiekt spadaj¹cego g³azu.
    /// 
    /// @param origin Punkt pocz¹tkowy rozrzutu.
    /// @param spread Zakres rozrzutu (X, Y, Z).
    /// @param speedMin Minimalna prêdkoœæ spadania.
    /// @param speedMax Maksymalna prêdkoœæ spadania.
    /// @param sizeMin Minimalny rozmiar g³azu.
    /// @param sizeMax Maksymalny rozmiar g³azu.
    /// @param deathY Wysokoœæ, poni¿ej której g³az zostaje usuniêty.
    /// @param boulderModel Model 3D u¿ywany do renderowania g³azu.
    /// @param rd Referencja do urz¹dzenia losowego.
    FallingBoulder(glm::vec3 origin, glm::vec3 spread, float speedMin,
        float speedMax, float sizeMin, float sizeMax, float deathY,
        Shape3D* boulderModel, std::random_device& rd);

    /// @brief Aktualizuje stan g³azu (pozycjê, kolizje, itp.).
    /// @param delta Czas delta w milisekundach.
    /// @param input Mapa wejœciowa (np. klawiatura/mysz).
    /// @param manager Mened¿er silnika.
    virtual void update(float delta, const InputMap& input, EngineManager* manager) override;

    /// @brief Renderuje g³az.
    /// @param view Macierz widoku (kamera).
    virtual void draw(const glm::mat4& view) override;

    /// @brief Inicjalizuje obiekt g³azu w kontekœcie silnika.
    /// @param initializer Obiekt inicjalizacyjny zawieraj¹cy zale¿noœci.
    /// @return true jeœli inicjalizacja powiod³a siê, false w przeciwnym razie.
    virtual bool init(Initializer* initializer) override;

    /// @brief Umieszcza g³az w losowej pozycji w okreœlonym obszarze rozrzutu.
    void place();
};
