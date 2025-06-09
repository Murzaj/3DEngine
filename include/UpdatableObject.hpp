#pragma once

class EngineManager;
class InputMap;
class Initializer;

#include "game/GameObject.hpp"

/// @brief Abstrakcyjna klasa bazowa dla obiektów aktualizowanych co klatkê.
/// 
/// Dziedziczy wirtualnie po GameObject, wymaga implementacji metody update.
/// Pozwala na aktualizacjê stanu obiektu z uwzglêdnieniem czasu, wejœcia oraz mened¿era silnika.
class UpdatableObject : public virtual GameObject {
public:
    /// @brief Wirtualna metoda aktualizuj¹ca stan obiektu.
    /// @param deltaMs Czas, jaki up³yn¹³ od ostatniej aktualizacji w milisekundach.
    /// @param input Referencja do mapy wejœcia u¿ytkownika.
    /// @param manager WskaŸnik do mened¿era silnika (mo¿e byæ nullptr).
    virtual void update(float deltaMs, const InputMap& input, EngineManager* manager) = 0;

    /// @brief Wirtualny destruktor domyœlny.
    virtual ~UpdatableObject() = default;

    /// @brief Inicjalizacja obiektu, wywo³uje bazow¹ inicjalizacjê klasy GameObject.
    /// @param initializer WskaŸnik do inicjalizatora.
    /// @return true jeœli inicjalizacja zakoñczy³a siê sukcesem, w przeciwnym razie false.
    virtual bool init(Initializer* initializer) override { return GameObject::init(initializer); }
};
