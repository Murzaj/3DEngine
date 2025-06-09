#pragma once

class EngineManager;
class InputMap;
class Initializer;

#include "game/GameObject.hpp"

/// @brief Abstrakcyjna klasa bazowa dla obiekt�w aktualizowanych co klatk�.
/// 
/// Dziedziczy wirtualnie po GameObject, wymaga implementacji metody update.
/// Pozwala na aktualizacj� stanu obiektu z uwzgl�dnieniem czasu, wej�cia oraz mened�era silnika.
class UpdatableObject : public virtual GameObject {
public:
    /// @brief Wirtualna metoda aktualizuj�ca stan obiektu.
    /// @param deltaMs Czas, jaki up�yn�� od ostatniej aktualizacji w milisekundach.
    /// @param input Referencja do mapy wej�cia u�ytkownika.
    /// @param manager Wska�nik do mened�era silnika (mo�e by� nullptr).
    virtual void update(float deltaMs, const InputMap& input, EngineManager* manager) = 0;

    /// @brief Wirtualny destruktor domy�lny.
    virtual ~UpdatableObject() = default;

    /// @brief Inicjalizacja obiektu, wywo�uje bazow� inicjalizacj� klasy GameObject.
    /// @param initializer Wska�nik do inicjalizatora.
    /// @return true je�li inicjalizacja zako�czy�a si� sukcesem, w przeciwnym razie false.
    virtual bool init(Initializer* initializer) override { return GameObject::init(initializer); }
};
