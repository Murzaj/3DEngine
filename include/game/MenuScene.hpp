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

/// @brief Struktura reprezentuj¹ca wpis w tablicy wyników.
struct ScoreEntry {
    std::string playerName; ///< Nazwa gracza.
    int score;              ///< Osi¹gniêty wynik.

    /// @brief Porównanie wpisów wg wyniku malej¹co.
    bool operator<(const ScoreEntry& other) const {
        return score > other.score;
    }
};

/// @brief Reprezentuje menu g³ówne gry oraz ekran koñca gry i tablicy wyników.
///
/// Klasa obs³uguje interaktywne przyciski menu, prze³¹czanie widoków (mapy, highscore, game over),
/// oraz rejestrowanie wyników gracza po zakoñczeniu gry.
class MenuScene : public UpdatableObject {
public:

    /// @brief Konstruktor inicjalizuj¹cy scenê menu z przekazanym silnikiem.
    /// @param engine WskaŸnik na g³ówny silnik gry.
    MenuScene(Engine* engine);

    /// @brief Destruktor klasy MenuScene.
    virtual ~MenuScene();

    /// @brief Inicjalizuje komponenty sceny menu.
    /// @param initializer Obiekt pomocniczy zawieraj¹cy zale¿noœci.
    /// @return true jeœli inicjalizacja siê powiod³a.
    bool init(Initializer* initializer) override;

    /// @brief G³ówna funkcja aktualizacji logiki menu.
    /// @param deltaMs Czas w milisekundach od ostatniej aktualizacji.
    /// @param input Obiekt mapy wejœciowej (klawiatura, mysz).
    /// @param manager WskaŸnik do silnika gry.
    void update(float deltaMs, const InputMap& input, EngineManager* manager) override;

    /// @brief Ustawia widocznoœæ g³ównego menu.
    void setActiveMenu(bool active);

    /// @brief Sprawdza, czy menu g³ówne jest aktywne.
    bool isActiveMenu() const;

    /// @brief Ustawia ekran koñca gry i ewentualnie inicjuje tryb wpisywania imienia.
    void setGameOver(bool active, int finalScore = 0);

    /// @brief Sprawdza, czy aktywny jest ekran koñca gry.
    bool isGameOver() const;

    /// @brief Zwraca wynik osi¹gniêty w zakoñczonej rozgrywce.
    int getScore() const;

    /// @brief Ustawia aktywnoœæ widoku wyboru mapy.
    void setActiveMapSelection(bool active);

    /// @brief Sprawdza, czy aktywny jest wybór mapy.
    bool isActiveMapSelection() const;

    /// @brief Ustawia tryb wpisywania imienia gracza do highscore.
    void setActiveEnteringName(bool active);

    /// @brief Sprawdza, czy aktywny jest tryb wpisywania imienia.
    bool isActiveEnteringName() const;

    /// @brief Ustawia tryb wyœwietlania tablicy wyników.
    void setActiveViewingHighScores(bool active);

    /// @brief Sprawdza, czy aktywny jest widok tablicy wyników.
    bool isActiveViewingHighScores() const;

    /// @brief Rysuje UI menu (placeholder – w³aœciwe rysowanie jest w silniku).
    void draw();

    /// @brief Struktura reprezentuj¹ca przycisk interfejsu u¿ytkownika.
    struct Button {
        std::string text; ///< Tekst na przycisku.
        float x, y;       ///< Pozycja na ekranie.
        float width, height; ///< Rozmiar przycisku.
        bool isHovered;   ///< Czy mysz znajduje siê nad przyciskiem.
        std::function<void()> action; ///< Funkcja wywo³ywana po klikniêciu.

        /// @brief Sprawdza, czy dane wspó³rzêdne znajduj¹ siê nad przyciskiem.
        bool isMouseOver(float mouseX, float mouseY) const {
            float left = x - width / 2.0f;
            float right = x + width / 2.0f;
            float bottom = y - height / 2.0f;
            float top = y + height / 2.0f;
            return (mouseX >= left && mouseX <= right &&
                mouseY >= bottom && mouseY <= top);
        }
    };

    /// @brief Zwraca listê przycisków menu g³ównego.
    const std::vector<Button>& getMenuButtons() const { return menuButtons; }

    /// @brief Zwraca listê przycisków ekranu koñca gry.
    const std::vector<Button>& getGameOverButtons() const { return gameOverButtons; }

    /// @brief Zwraca listê przycisków wyboru mapy.
    const std::vector<Button>& getMapSelectionButtons() const { return mapSelectionButtons; }

    /// @brief Zwraca listê przycisków tablicy wyników.
    const std::vector<Button>& getHighScoreButtons() const { return highScoreButtons; }

    /// @brief Nieu¿ywane – zwraca nullptr.
    Shape3D* getShape() const { return nullptr; }

    /// @brief Dodaje wynik gracza do tablicy wyników.
    void addScore(const std::string& name, int scoreValue);

    /// @brief Sprawdza, czy wynik kwalifikuje siê do zapisania w top wynikach.
    bool isHighScore(int scoreValue) const;

    /// @brief Zwraca wektor najlepszych wyników.
    const std::vector<ScoreEntry>& getHighScores() const { return highScores; }

    /// @brief Zwraca imiê obecnie wpisywane przez gracza.
    std::string getCurrentPlayerName() const { return currentPlayerName; }

    /// @brief Zwraca wynik przypisany do wpisu w tablicy wyników.
    int getCurrentScoreForEntry() const { return currentScoreForEntry; }

    static const int MAX_NAME_LENGTH = 15; ///< Maksymalna d³ugoœæ imienia gracza.

private:
    Engine* enginePtr; ///< WskaŸnik do g³ównego silnika.
    bool menuActive;   ///< Czy menu g³ówne jest aktywne.
    bool gameOverActive; ///< Czy ekran koñca gry jest aktywny.
    bool mapSelectionActive; ///< Czy widok wyboru mapy jest aktywny.
    bool enteringNameActive; ///< Czy trwa wpisywanie imienia gracza.
    bool viewingHighScoresActive; ///< Czy aktywna jest tablica wyników.

    int score; ///< Ostatni uzyskany wynik.
    int currentScoreForEntry; ///< Wynik do przypisania w tablicy wyników.
    std::string currentPlayerName; ///< Obecnie wpisywane imiê gracza.

    std::vector<Button> menuButtons;        ///< Przycisk menu g³ównego.
    std::vector<Button> gameOverButtons;    ///< Przycisk ekranu koñca gry.
    std::vector<Button> mapSelectionButtons;///< Przycisk wyboru mapy.
    std::vector<Button> highScoreButtons;   ///< Przycisk widoku wyników.

    void setupMenuButtons();            ///< Inicjalizuje przyciski menu g³ównego.
    void setupGameOverButtons();        ///< Inicjalizuje przyciski ekranu koñca gry.
    void setupMapSelectionButtons();    ///< Inicjalizuje przyciski wyboru mapy.
    void setupHighScoreButtons();       ///< Inicjalizuje przyciski tablicy wyników.

    std::vector<ScoreEntry> highScores; ///< Lista wyników graczy.
    static const int MAX_HIGH_SCORES = 10; ///< Maksymalna liczba przechowywanych wyników.
    const std::string highScoreFilename = "highscores.txt"; ///< Nazwa pliku z wynikami.

    void loadHighScores(); ///< Wczytuje wyniki z pliku.
    void saveHighScores(); ///< Zapisuje wyniki do pliku.

    // Akcje przypisane do przycisków
    static void startGameAction(); ///< Uruchamia grê.
    static void exitGameAction(); ///< Zamyka aplikacjê.
    static void restartGameAction(); ///< Restartuje grê po zakoñczeniu.
    static void backToMenuAction(); ///< Powrót do menu g³ównego.
    static void openMapSelectionAction(); ///< Otwiera widok wyboru mapy.
    static void backToMainMenuActionFromMapSelection(); ///< Powrót z mapy do menu.
    static void openHighScoresAction(); ///< Przejœcie do tablicy wyników.
    static void submitNameAction(); ///< Zatwierdza wpisane imiê i zapisuje wynik.
};
