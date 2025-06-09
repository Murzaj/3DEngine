#pragma once 

#include <glm/glm.hpp>
#include <unordered_map>
#include <unordered_set>

/// @brief Struktura reprezentuj�ca stan przycisk�w myszy.
/// 
/// Przechowuje informacje o tym, czy dany przycisk myszy (lewy, prawy, �rodkowy) jest aktualnie wci�ni�ty.
struct MouseButtons {
    bool left = false;   ///< Czy lewy przycisk jest wci�ni�ty.
    bool right = false;  ///< Czy prawy przycisk jest wci�ni�ty.
    bool middle = false; ///< Czy �rodkowy przycisk jest wci�ni�ty.
};

/// @brief Klasa mapuj�ca i �ledz�ca dane wej�ciowe (klawiatura, mysz).
///
/// Obs�uguje aktualny i poprzedni stan klawiszy, pozycj� myszy, przyciski oraz kierunek przewijania.
/// Umo�liwia wykrycie zdarze� typu �klawisz zosta� wci�ni�ty�, �klawisz zosta� puszczony� oraz przesuni�cie myszy.
class InputMap {
public:
    /// @brief Sta�a reprezentuj�ca pseudoklawisz dla klikni�cia lewym przyciskiem myszy.
    static const unsigned char MOUSE_LEFT_CLICK_PSEUDO_KEY = 250; // Jaka� warto�� spoza ASCII

    /// @brief Sprawdza, czy klawisz jest aktualnie wci�ni�ty.
    /// @param key Kod klawisza.
    /// @return true je�li klawisz jest wci�ni�ty, w przeciwnym razie false.
    bool isKeyDown(unsigned char key) const;

    /// @brief Sprawdza, czy klawisz zosta� w�a�nie wci�ni�ty w tej klatce.
    /// @param key Kod klawisza.
    /// @return true je�li klawisz zosta� w�a�nie wci�ni�ty, w przeciwnym razie false.
    bool isKeyJustPressed(unsigned char key) const;

    /// @brief Sprawdza, czy klawisz zosta� w�a�nie puszczony w tej klatce.
    /// @param key Kod klawisza.
    /// @return true je�li klawisz zosta� w�a�nie puszczony, w przeciwnym razie false.
    bool isKeyJustReleased(unsigned char key) const;

    /// @brief Zwraca wektor przesuni�cia myszy wzgl�dem poprzedniej klatki.
    /// @return Wektor 2D reprezentuj�cy przesuni�cie.
    glm::vec2 getMouseDelta() const;

    /// @brief Zwraca aktualn� pozycj� myszy.
    /// @return Wektor 2D z bie��c� pozycj� kursora.
    glm::vec2 getMousePosition() const;

    /// @brief Zwraca struktur� opisuj�c� stan przycisk�w myszy.
    /// @return Struktura MouseButtons.
    MouseButtons getMouseButtons() const;

    /// @brief Zwraca kierunek przewijania k�kiem myszy.
    /// @return Liczba ca�kowita reprezentuj�ca kierunek (np. -1, 0, 1).
    int getWheelDirection() const;

    /// @brief Ustawia stan klawisza jako wci�ni�ty.
    /// @param key Kod klawisza.
    void setKeyDown(unsigned char key);

    /// @brief Ustawia stan klawisza jako puszczony.
    /// @param key Kod klawisza.
    void setKeyUp(unsigned char key);

    /// @brief Ustawia stan lewego przycisku myszy jako wci�ni�ty.
    void setLeftClickDown();

    /// @brief Ustawia stan lewego przycisku myszy jako puszczony.
    void setLeftClickUp();

    /// @brief Ustawia stan prawego przycisku myszy jako wci�ni�ty.
    void setRightClickDown();

    /// @brief Ustawia stan prawego przycisku myszy jako puszczony.
    void setRightClickUp();

    /// @brief Ustawia stan �rodkowego przycisku myszy jako wci�ni�ty.
    void setMiddleClickDown();

    /// @brief Ustawia stan �rodkowego przycisku myszy jako puszczony.
    void setMiddleClickUp();

    /// @brief Ustawia aktualn� pozycj� kursora myszy.
    /// @param x Pozycja X kursora.
    /// @param y Pozycja Y kursora.
    void setMousePosition(int x, int y);

    /// @brief Ustawia kierunek przewijania k�kiem myszy.
    /// @param direction Kierunek przewijania (np. -1, 0, 1).
    void setWheelDirection(int direction);

    /// @brief Aktualizuje stan wej�cia mi�dzy klatkami.
    ///
    /// Przenosi aktualny stan klawiszy i pozycji myszy do poprzedniego stanu
    /// oraz oblicza nowe przesuni�cie myszy.
    void updateFrameState();

private:
    std::unordered_set<unsigned char> currentKeys;   ///< Klawisze aktualnie wci�ni�te.
    std::unordered_set<unsigned char> previousKeys;  ///< Klawisze wci�ni�te w poprzedniej klatce.

    MouseButtons buttons;                ///< Stan przycisk�w myszy.
    glm::vec2 currentMousePos = glm::vec2(0.0f);   ///< Aktualna pozycja myszy.
    glm::vec2 previousMousePos = glm::vec2(0.0f);  ///< Pozycja myszy w poprzedniej klatce.
    glm::vec2 mouseDelta = glm::vec2(0.0f);        ///< Przesuni�cie myszy od poprzedniej klatki.
    int wheelDirection = 0;                        ///< Kierunek przewijania k�kiem myszy.
};
