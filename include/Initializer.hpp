#pragma once

class BitmapHandler;
class EngineManager;

/// @brief Interfejs inicjalizatora komponentów systemu.
/// 
/// Umo¿liwia dostêp do podstawowych elementów silnika gry, takich jak obs³uga bitmap oraz mened¿er silnika.
/// Klasa ta pe³ni rolê abstrakcyjnego interfejsu dla inicjalizacji kluczowych komponentów systemu.
class Initializer {
public:
    /// @brief Wirtualny destruktor.
    virtual ~Initializer() = default;

    /// @brief Zwraca wskaŸnik do obiektu obs³uguj¹cego bitmapy.
    /// @return WskaŸnik na BitmapHandler.
    virtual BitmapHandler* getBitmapHandler() = 0;

    /// @brief Zwraca wskaŸnik do mened¿era silnika.
    /// @return WskaŸnik na EngineManager.
    virtual EngineManager* getEngineManager() = 0;
};
