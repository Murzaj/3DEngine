#pragma once

#include <typeinfo> 

class GameObject;

/// @brief Interfejs mened�era silnika gry.
///
/// Umo�liwia dodawanie, usuwanie i wyszukiwanie obiekt�w gry.
/// Klasa ta s�u�y jako abstrakcyjny interfejs, kt�ry mo�e by� implementowany przez r�ne systemy zarz�dzaj�ce logik� gry.
class EngineManager {
public:
    /// @brief Wirtualny destruktor.
    virtual ~EngineManager() = default;

    /// @brief Dodaje obiekt do zarz�dzanego �wiata gry.
    /// @param obj Wska�nik na obiekt do dodania.
    virtual void addObject(GameObject* obj) = 0;

    /// @brief Usuwa obiekt z zarz�dzanego �wiata gry.
    /// @param obj Wska�nik na obiekt do usuni�cia.
    virtual void removeObject(GameObject* obj) = 0;

    /// @brief Zwraca pierwszy obiekt danego typu.
    /// @param type Typ obiektu (np. typeid(Player)).
    /// @return Wska�nik na znaleziony obiekt lub nullptr, je�li brak.
    virtual GameObject* getFirstOfType(const std::type_info& type) const = 0;

    /// @brief Zatrzymuje dzia�anie gry.
    virtual void stop() = 0;
};
