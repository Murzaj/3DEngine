#pragma once

#include "UpdatableObject.hpp"
#include "InputMap.hpp"
#include "EngineManager.hpp"
#include "Initializer.hpp"
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <fstream>
#include <iomanip>

class Engine; // Forward declaration

/// @brief Struktura reprezentuj�ca wpis w tablicy wynik�w.
struct ScoreEntry {
    std::string playerName; ///< Nazwa gracza.
    int score;              ///< Osi�gni�ty wynik.

    /// @brief Por�wnanie wpis�w wg wyniku malej�co.
    bool operator<(const ScoreEntry& other) const {
        return score > other.score;
    }
};

/// @brief Reprezentuje menu g��wne gry oraz ekran ko�ca gry i tablicy wynik�w.
///
/// Klasa obs�uguje interaktywne przyciski menu, prze��czanie widok�w (mapy, highscore, game over),
/// oraz rejestrowanie wynik�w gracza po zako�czeniu gry.
class MenuScene : public UpdatableObject {
public:

    /// @brief Konstruktor inicjalizuj�cy scen� menu z przekazanym silnikiem.
    /// @param engine Wska�nik na g��wny silnik gry.
    MenuScene(Engine* engine);

    /// @brief Destruktor klasy MenuScene.
    virtual ~MenuScene();

    /// @brief Inicjalizuje komponenty sceny menu.
    /// @param initializer Obiekt pomocniczy zawieraj�cy zale�no�ci.
    /// @return true je�li inicjalizacja si� powiod�a.
    bool init(Initializer* initializer) override;

    /// @brief G��wna funkcja aktualizacji logiki menu.
    /// @param deltaMs Czas w milisekundach od ostatniej aktualizacji.
    /// @param input Obiekt mapy wej�ciowej (klawiatura, mysz).
    /// @param manager Wska�nik do silnika gry.
    void update(float deltaMs, const InputMap& input, EngineManager* manager) override;

    /// @brief Ustawia widoczno�� g��wnego menu.
    void setActiveMenu(bool active);

    /// @brief Sprawdza, czy menu g��wne jest aktywne.
    bool isActiveMenu() const;

    /// @brief Ustawia ekran ko�ca gry i ewentualnie inicjuje tryb wpisywania imienia.
    void setGameOver(bool active, int finalScore = 0);

    /// @brief Sprawdza, czy aktywny jest ekran ko�ca gry.
    bool isGameOver() const;

    /// @brief Zwraca wynik osi�gni�ty w zako�czonej rozgrywce.
    int getScore() const;

    /// @brief Ustawia aktywno�� widoku wyboru mapy.
    void setActiveMapSelection(bool active);

    /// @brief Sprawdza, czy aktywny jest wyb�r mapy.
    bool isActiveMapSelection() const;

    /// @brief Ustawia tryb wpisywania imienia gracza do highscore.
    void setActiveEnteringName(bool active);

    /// @brief Sprawdza, czy aktywny jest tryb wpisywania imienia.
    bool isActiveEnteringName() const;

    /// @brief Ustawia tryb wy�wietlania tablicy wynik�w.
    void setActiveViewingHighScores(bool active);

    /// @brief Sprawdza, czy aktywny jest widok tablicy wynik�w.
    bool isActiveViewingHighScores() const;

    /// @brief Rysuje UI menu (placeholder � w�a�ciwe rysowanie jest w silniku).
    void draw();

    /// @brief Struktura reprezentuj�ca przycisk interfejsu u�ytkownika.
    struct Button {
        std::string text; ///< Tekst na przycisku.
        float x, y;       ///< Pozycja na ekranie.
        float width, height; ///< Rozmiar przycisku.
        bool isHovered;   ///< Czy mysz znajduje si� nad przyciskiem.
        std::function<void()> action; ///< Funkcja wywo�ywana po klikni�ciu.

        /// @brief Sprawdza, czy dane wsp�rz�dne znajduj� si� nad przyciskiem.
        bool isMouseOver(float mouseX, float mouseY) const {
            float left = x - width / 2.0f;
            float right = x + width / 2.0f;
            float bottom = y - height / 2.0f;
            float top = y + height / 2.0f;
            return (mouseX >= left && mouseX <= right &&
                mouseY >= bottom && mouseY <= top);
        }
    };

    /// @brief Zwraca list� przycisk�w menu g��wnego.
    const std::vector<Button>& getMenuButtons() const { return menuButtons; }

    /// @brief Zwraca list� przycisk�w ekranu ko�ca gry.
    const std::vector<Button>& getGameOverButtons() const { return gameOverButtons; }

    /// @brief Zwraca list� przycisk�w wyboru mapy.
    const std::vector<Button>& getMapSelectionButtons() const { return mapSelectionButtons; }

    /// @brief Zwraca list� przycisk�w tablicy wynik�w.
    const std::vector<Button>& getHighScoreButtons() const { return highScoreButtons; }

    /// @brief Nieu�ywane � zwraca nullptr.
    Shape3D* getShape() const { return nullptr; }

    /// @brief Dodaje wynik gracza do tablicy wynik�w.
    void addScore(const std::string& name, int scoreValue);

    /// @brief Sprawdza, czy wynik kwalifikuje si� do zapisania w top wynikach.
    bool isHighScore(int scoreValue) const;

    /// @brief Zwraca wektor najlepszych wynik�w.
    const std::vector<ScoreEntry>& getHighScores() const { return highScores; }

    /// @brief Zwraca imi� obecnie wpisywane przez gracza.
    std::string getCurrentPlayerName() const { return currentPlayerName; }

    /// @brief Zwraca wynik przypisany do wpisu w tablicy wynik�w.
    int getCurrentScoreForEntry() const { return currentScoreForEntry; }

    static const int MAX_NAME_LENGTH = 15; ///< Maksymalna d�ugo�� imienia gracza.

private:
    Engine* enginePtr; ///< Wska�nik do g��wnego silnika.
    bool menuActive;   ///< Czy menu g��wne jest aktywne.
    bool gameOverActive; ///< Czy ekran ko�ca gry jest aktywny.
    bool mapSelectionActive; ///< Czy widok wyboru mapy jest aktywny.
    bool enteringNameActive; ///< Czy trwa wpisywanie imienia gracza.
    bool viewingHighScoresActive; ///< Czy aktywna jest tablica wynik�w.

    int score; ///< Ostatni uzyskany wynik.
    int currentScoreForEntry; ///< Wynik do przypisania w tablicy wynik�w.
    std::string currentPlayerName; ///< Obecnie wpisywane imi� gracza.

    std::vector<Button> menuButtons;        ///< Przycisk menu g��wnego.
    std::vector<Button> gameOverButtons;    ///< Przycisk ekranu ko�ca gry.
    std::vector<Button> mapSelectionButtons;///< Przycisk wyboru mapy.
    std::vector<Button> highScoreButtons;   ///< Przycisk widoku wynik�w.

    void setupMenuButtons();            ///< Inicjalizuje przyciski menu g��wnego.
    void setupGameOverButtons();        ///< Inicjalizuje przyciski ekranu ko�ca gry.
    void setupMapSelectionButtons();    ///< Inicjalizuje przyciski wyboru mapy.
    void setupHighScoreButtons();       ///< Inicjalizuje przyciski tablicy wynik�w.

    std::vector<ScoreEntry> highScores; ///< Lista wynik�w graczy.
    static const int MAX_HIGH_SCORES = 10; ///< Maksymalna liczba przechowywanych wynik�w.
    const std::string highScoreFilename = "highscores.txt"; ///< Nazwa pliku z wynikami.

    void loadHighScores(); ///< Wczytuje wyniki z pliku.
    void saveHighScores(); ///< Zapisuje wyniki do pliku.

    // Akcje przypisane do przycisk�w
    static void startGameAction(); ///< Uruchamia gr�.
    static void exitGameAction(); ///< Zamyka aplikacj�.
    static void restartGameAction(); ///< Restartuje gr� po zako�czeniu.
    static void backToMenuAction(); ///< Powr�t do menu g��wnego.
    static void openMapSelectionAction(); ///< Otwiera widok wyboru mapy.
    static void backToMainMenuActionFromMapSelection(); ///< Powr�t z mapy do menu.
    static void openHighScoresAction(); ///< Przej�cie do tablicy wynik�w.
    static void submitNameAction(); ///< Zatwierdza wpisane imi� i zapisuje wynik.
};
