#pragma once 

#include <glm/glm.hpp>
#include <unordered_map>
#include <unordered_set>

/// @brief Struktura reprezentuj¹ca stan przycisków myszy.
/// 
/// Przechowuje informacje o tym, czy dany przycisk myszy (lewy, prawy, œrodkowy) jest aktualnie wciœniêty.
struct MouseButtons {
    bool left = false;   ///< Czy lewy przycisk jest wciœniêty.
    bool right = false;  ///< Czy prawy przycisk jest wciœniêty.
    bool middle = false; ///< Czy œrodkowy przycisk jest wciœniêty.
};

/// @brief Klasa mapuj¹ca i œledz¹ca dane wejœciowe (klawiatura, mysz).
///
/// Obs³uguje aktualny i poprzedni stan klawiszy, pozycjê myszy, przyciski oraz kierunek przewijania.
/// Umo¿liwia wykrycie zdarzeñ typu „klawisz zosta³ wciœniêty”, „klawisz zosta³ puszczony” oraz przesuniêcie myszy.
class InputMap {
public:
    /// @brief Sta³a reprezentuj¹ca pseudoklawisz dla klikniêcia lewym przyciskiem myszy.
    static const unsigned char MOUSE_LEFT_CLICK_PSEUDO_KEY = 250; // Jakaœ wartoœæ spoza ASCII

    /// @brief Sprawdza, czy klawisz jest aktualnie wciœniêty.
    /// @param key Kod klawisza.
    /// @return true jeœli klawisz jest wciœniêty, w przeciwnym razie false.
    bool isKeyDown(unsigned char key) const;

    /// @brief Sprawdza, czy klawisz zosta³ w³aœnie wciœniêty w tej klatce.
    /// @param key Kod klawisza.
    /// @return true jeœli klawisz zosta³ w³aœnie wciœniêty, w przeciwnym razie false.
    bool isKeyJustPressed(unsigned char key) const;

    /// @brief Sprawdza, czy klawisz zosta³ w³aœnie puszczony w tej klatce.
    /// @param key Kod klawisza.
    /// @return true jeœli klawisz zosta³ w³aœnie puszczony, w przeciwnym razie false.
    bool isKeyJustReleased(unsigned char key) const;

    /// @brief Zwraca wektor przesuniêcia myszy wzglêdem poprzedniej klatki.
    /// @return Wektor 2D reprezentuj¹cy przesuniêcie.
    glm::vec2 getMouseDelta() const;

    /// @brief Zwraca aktualn¹ pozycjê myszy.
    /// @return Wektor 2D z bie¿¹c¹ pozycj¹ kursora.
    glm::vec2 getMousePosition() const;

    /// @brief Zwraca strukturê opisuj¹c¹ stan przycisków myszy.
    /// @return Struktura MouseButtons.
    MouseButtons getMouseButtons() const;

    /// @brief Zwraca kierunek przewijania kó³kiem myszy.
    /// @return Liczba ca³kowita reprezentuj¹ca kierunek (np. -1, 0, 1).
    int getWheelDirection() const;

    /// @brief Ustawia stan klawisza jako wciœniêty.
    /// @param key Kod klawisza.
    void setKeyDown(unsigned char key);

    /// @brief Ustawia stan klawisza jako puszczony.
    /// @param key Kod klawisza.
    void setKeyUp(unsigned char key);

    /// @brief Ustawia stan lewego przycisku myszy jako wciœniêty.
    void setLeftClickDown();

    /// @brief Ustawia stan lewego przycisku myszy jako puszczony.
    void setLeftClickUp();

    /// @brief Ustawia stan prawego przycisku myszy jako wciœniêty.
    void setRightClickDown();

    /// @brief Ustawia stan prawego przycisku myszy jako puszczony.
    void setRightClickUp();

    /// @brief Ustawia stan œrodkowego przycisku myszy jako wciœniêty.
    void setMiddleClickDown();

    /// @brief Ustawia stan œrodkowego przycisku myszy jako puszczony.
    void setMiddleClickUp();

    /// @brief Ustawia aktualn¹ pozycjê kursora myszy.
    /// @param x Pozycja X kursora.
    /// @param y Pozycja Y kursora.
    void setMousePosition(int x, int y);

    /// @brief Ustawia kierunek przewijania kó³kiem myszy.
    /// @param direction Kierunek przewijania (np. -1, 0, 1).
    void setWheelDirection(int direction);

    /// @brief Aktualizuje stan wejœcia miêdzy klatkami.
    ///
    /// Przenosi aktualny stan klawiszy i pozycji myszy do poprzedniego stanu
    /// oraz oblicza nowe przesuniêcie myszy.
    void updateFrameState();

private:
    std::unordered_set<unsigned char> currentKeys;   ///< Klawisze aktualnie wciœniête.
    std::unordered_set<unsigned char> previousKeys;  ///< Klawisze wciœniête w poprzedniej klatce.

    MouseButtons buttons;                ///< Stan przycisków myszy.
    glm::vec2 currentMousePos = glm::vec2(0.0f);   ///< Aktualna pozycja myszy.
    glm::vec2 previousMousePos = glm::vec2(0.0f);  ///< Pozycja myszy w poprzedniej klatce.
    glm::vec2 mouseDelta = glm::vec2(0.0f);        ///< Przesuniêcie myszy od poprzedniej klatki.
    int wheelDirection = 0;                        ///< Kierunek przewijania kó³kiem myszy.
};
