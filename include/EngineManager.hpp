#pragma once

#include <typeinfo> 

class GameObject;

/// @brief Interfejs mened¿era silnika gry.
///
/// Umo¿liwia dodawanie, usuwanie i wyszukiwanie obiektów gry.
/// Klasa ta s³u¿y jako abstrakcyjny interfejs, który mo¿e byæ implementowany przez ró¿ne systemy zarz¹dzaj¹ce logik¹ gry.
class EngineManager {
public:
    /// @brief Wirtualny destruktor.
    virtual ~EngineManager() = default;

    /// @brief Dodaje obiekt do zarz¹dzanego œwiata gry.
    /// @param obj WskaŸnik na obiekt do dodania.
    virtual void addObject(GameObject* obj) = 0;

    /// @brief Usuwa obiekt z zarz¹dzanego œwiata gry.
    /// @param obj WskaŸnik na obiekt do usuniêcia.
    virtual void removeObject(GameObject* obj) = 0;

    /// @brief Zwraca pierwszy obiekt danego typu.
    /// @param type Typ obiektu (np. typeid(Player)).
    /// @return WskaŸnik na znaleziony obiekt lub nullptr, jeœli brak.
    virtual GameObject* getFirstOfType(const std::type_info& type) const = 0;

    /// @brief Zatrzymuje dzia³anie gry.
    virtual void stop() = 0;
};
