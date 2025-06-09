#pragma once
#include "UpdatableObject.hpp"
#include "Shape3D.hpp"
#include "game/Player.hpp"
#include <random>

/// @brief Reprezentuje spadaj�cy g�az w �wiecie gry.
///
/// Klasa odpowiedzialna za tworzenie, rysowanie i aktualizacj� pozycji spadaj�cych g�az�w.
/// G�azy pojawiaj� si� losowo w zadanym obszarze i znikaj� po przekroczeniu okre�lonej wysoko�ci.
class FallingBoulder : public UpdatableObject, public Shape3D {
protected:
    float speed;                                ///< Pr�dko�� spadania g�azu.
    glm::vec3 pos;                               ///< Aktualna pozycja g�azu.
    glm::vec3 origin;                            ///< Punkt pocz�tkowy rozrzutu.
    glm::vec3 spread;                            ///< Zakres rozrzutu pozycji.
    float size;                                  ///< Rozmiar g�azu.
    float deathY;                                ///< Pozycja Y, poni�ej kt�rej g�az znika.
    Shape3D* boulderModel;                       ///< Model 3D reprezentuj�cy g�az.
    Player* player;                              ///< Wska�nik na gracza (do detekcji kolizji lub interakcji).

    std::random_device rd;                       ///< Urz�dzenie losuj�ce (dla RNG).
    std::uniform_real_distribution<float> xDistribution; ///< Rozrzut wsp�rz�dnej X.
    std::uniform_real_distribution<float> yDistribution; ///< Rozrzut wsp�rz�dnej Y.
    std::uniform_real_distribution<float> zDistribution; ///< Rozrzut wsp�rz�dnej Z.
    std::uniform_real_distribution<float> speedDistribution; ///< Rozrzut pr�dko�ci.
    std::uniform_real_distribution<float> sizeDistribution;  ///< Rozrzut rozmiaru.
    std::mt19937 rng;                            ///< Generator liczb pseudolosowych.

public:

    /// @brief Tworzy nowy obiekt spadaj�cego g�azu.
    /// 
    /// @param origin Punkt pocz�tkowy rozrzutu.
    /// @param spread Zakres rozrzutu (X, Y, Z).
    /// @param speedMin Minimalna pr�dko�� spadania.
    /// @param speedMax Maksymalna pr�dko�� spadania.
    /// @param sizeMin Minimalny rozmiar g�azu.
    /// @param sizeMax Maksymalny rozmiar g�azu.
    /// @param deathY Wysoko��, poni�ej kt�rej g�az zostaje usuni�ty.
    /// @param boulderModel Model 3D u�ywany do renderowania g�azu.
    /// @param rd Referencja do urz�dzenia losowego.
    FallingBoulder(glm::vec3 origin, glm::vec3 spread, float speedMin,
        float speedMax, float sizeMin, float sizeMax, float deathY,
        Shape3D* boulderModel, std::random_device& rd);

    /// @brief Aktualizuje stan g�azu (pozycj�, kolizje, itp.).
    /// @param delta Czas delta w milisekundach.
    /// @param input Mapa wej�ciowa (np. klawiatura/mysz).
    /// @param manager Mened�er silnika.
    virtual void update(float delta, const InputMap& input, EngineManager* manager) override;

    /// @brief Renderuje g�az.
    /// @param view Macierz widoku (kamera).
    virtual void draw(const glm::mat4& view) override;

    /// @brief Inicjalizuje obiekt g�azu w kontek�cie silnika.
    /// @param initializer Obiekt inicjalizacyjny zawieraj�cy zale�no�ci.
    /// @return true je�li inicjalizacja powiod�a si�, false w przeciwnym razie.
    virtual bool init(Initializer* initializer) override;

    /// @brief Umieszcza g�az w losowej pozycji w okre�lonym obszarze rozrzutu.
    void place();
};
