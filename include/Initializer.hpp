#pragma once

class BitmapHandler;
class EngineManager;

/// @brief Interfejs inicjalizatora komponent�w systemu.
/// 
/// Umo�liwia dost�p do podstawowych element�w silnika gry, takich jak obs�uga bitmap oraz mened�er silnika.
/// Klasa ta pe�ni rol� abstrakcyjnego interfejsu dla inicjalizacji kluczowych komponent�w systemu.
class Initializer {
public:
    /// @brief Wirtualny destruktor.
    virtual ~Initializer() = default;

    /// @brief Zwraca wska�nik do obiektu obs�uguj�cego bitmapy.
    /// @return Wska�nik na BitmapHandler.
    virtual BitmapHandler* getBitmapHandler() = 0;

    /// @brief Zwraca wska�nik do mened�era silnika.
    /// @return Wska�nik na EngineManager.
    virtual EngineManager* getEngineManager() = 0;
};
