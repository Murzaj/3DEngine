#pragma once  

#include <GL/glew.h>
#include <GL/freeglut.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <string>
#include <vector>
#include <memory>
#include <typeinfo>
#include <functional> 

#include "SoundHandler.hpp"
#include "Initializer.hpp"
#include "EngineManager.hpp"
#include "BitmapHandler.hpp"
#include "Observer.hpp"
#include "InputMap.hpp"
#include "game/MenuScene.hpp"

class GameObject;
class UpdatableObject;
class Shape3D;
class GameScene;

/// @brief Typ enumeracyjny reprezentuj¹cy dostêpne mapy w grze.
enum class GameMap {
    NIEBO,
    DZUNGLA,
    LODOWA,
    WULKAN,
    PUSTYNIA
};

/// @brief Typ enumeracyjny reprezentuj¹cy aktualny stan gry.
enum class GameState {
    MENU,
    IN_GAME,
    GAME_OVER
};

/// @brief G³ówna klasa silnika gry.
///
/// Odpowiada za zarz¹dzanie renderowaniem, scenami, dŸwiêkiem,
/// wejœciem, cyklem ¿ycia gry oraz obiektami w grze. Obs³uguje te¿ ustawienia kamery,
/// œwiat³a, tekstur i tryby gry.
class Engine : public Initializer, public EngineManager {
protected:
    static Engine* instance; ///< WskaŸnik do singletona silnika.
    std::string name; ///< Nazwa okna gry.

    std::unique_ptr<Observer> observer = nullptr; ///< Kamera/obserwator sceny.
    glm::mat4 projection; ///< Macierz projekcji.
    float farPlane; ///< Zasiêg widzenia (daleki plan).
    float nearPlane; ///< Zasiêg widzenia (bliski plan).
    float fov; ///< K¹t widzenia kamery w stopniach.

    std::unique_ptr<SoundHandler> soundHandler; ///< Obs³uga dŸwiêków.
    std::vector<GameObject*> objects; ///< Obiekty gry.
    std::vector<UpdatableObject*> updatables; ///< Obiekty aktualizowane w pêtli gry.
    std::vector<Shape3D*> shapes; ///< Obiekty do renderowania.
    std::vector<GameObject*> cleanupQueue; ///< Kolejka do usuniêcia.

    std::unique_ptr<InputMap> inputMap; ///< Mapa wejœæ u¿ytkownika.

    float fixedUpdateMs; ///< Interwa³ aktualizacji logiki (sta³y czas delta).

    int width; ///< Szerokoœæ okna gry.
    int height; ///< Wysokoœæ okna gry.
    unsigned int displayMode; ///< Tryb wyœwietlania OpenGL.
    bool fullscreen; ///< Czy gra dzia³a w trybie pe³noekranowym.

    std::unique_ptr<BitmapHandler> bitmapHandler; ///< Mened¿er tekstur.
    MenuScene* menuScene = nullptr; ///< WskaŸnik na scenê menu.
    GameScene* gameScene = nullptr; ///< WskaŸnik na aktywn¹ scenê gry.

    bool lightingEnabled = true; ///< Czy oœwietlenie OpenGL jest aktywne.
    bool warped = false; ///< Czy kursor zosta³ przesuniêty programowo.
    bool running = true; ///< Czy gra dzia³a.

    void (*keyboardCallback)(unsigned char, int, int) = nullptr; ///< Callback klawiatury.
    void (*updateCallback)(float) = nullptr; ///< Callback aktualizacji logiki.

    GameState currentGameState = GameState::MENU; ///< Aktualny stan gry.

    // --- Funkcje pomocnicze ---
    void prepareObjects();
    void cleanupObjects();
    void processCleanupQueue();
    void prepareCallbacks();
    void setupTimer();
    void fixedUpdate();
    void display();
    void mainLoopInternal();

    // Tekstury t³a dla map
    GLuint nieboBackgroundTextureID = 0;
    GLuint dzunglaBackgroundTextureID = 0;
    GLuint lodowaBackgroundTextureID = 0;
    GLuint wulkanBackgroundTextureID = 0;
    GLuint pustyniaBackgroundTextureID = 0;

    GameMap selectedGameMap = GameMap::NIEBO; ///< Wybrana mapa.

    /// @brief Rysuje tekst 2D w oknie.
    void drawText(float x, float y, const std::string& text, void* font = GLUT_BITMAP_9_BY_15, float r = 1.0f, float g = 1.0f, float b = 1.0f, float scaleFactor = 1.0f);

    /// @brief Rysuje interfejs menu.
    void drawMenuUI();

    // --- Wrappery statyczne do GLUT ---
    static void displayWrapper() { if (instance) instance->display(); }
    static void fixedUpdateWrapper(int value) { if (instance) instance->fixedUpdate(); }
    static void reshapeWrapper(int w, int h) { if (instance) instance->onReshape(w, h); }
    static void keyboardWrapper(unsigned char k, int x, int y) { if (instance) instance->onKeyboard(k, x, y); }
    static void keyboardUpWrapper(unsigned char k, int x, int y) { if (instance) instance->onKeyboardUp(k, x, y); }
    static void specialWrapper(int k, int x, int y) { if (instance) instance->onSpecial(k, x, y); }
    static void specialUpWrapper(int k, int x, int y) { if (instance) instance->onSpecialUp(k, x, y); }
    static void motionWrapper(int x, int y) { if (instance) instance->onMotion(x, y); }
    static void passiveMotionWrapper(int x, int y) { if (instance) instance->onPassiveMotion(x, y); }
    static void mouseWheelWrapper(int w, int d, int x, int y) { if (instance) instance->onMouseWheel(w, d, x, y); }
    static void mouseFuncWrapper(int b, int s, int x, int y) { if (instance) instance->onMouseFunc(b, s, x, y); }
    static void closeWrapper() { if (instance) instance->stop(); }

    // --- Obs³uga zdarzeñ ---
    void onKeyboard(unsigned char key, int x, int y);
    void onSpecial(int key, int x, int y);
    void onSpecialUp(int key, int x, int y);
    void onKeyboardUp(unsigned char key, int x, int y);
    void onReshape(int width, int height);
    void onMotion(int x, int y);
    void onPassiveMotion(int x, int y);
    void onMouseWheel(int wheel, int direction, int x, int y);
    void onMouseFunc(int button, int state, int x, int y);

public:
    /// @brief Konstruktor silnika gry.
    Engine();

    /// @brief Destruktor silnika gry.
    virtual ~Engine();

    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    /// @brief Zwraca wskaŸnik do handlera dŸwiêku.
    SoundHandler* getSoundHandler() { return soundHandler.get(); }

    /// @brief Inicjalizuje silnik i konfiguruje GLUT.
    bool initialize(int* argc, char* argv[]);

    /// @brief Uruchamia silnik.
    void run();

    /// @brief G³ówna pêtla gry.
    void mainLoop();

    /// @brief Ustawia nazwê okna.
    void setWindowName(const std::string& name);

    /// @brief Ustawia kolor czyszczenia t³a.
    void setClearColor(const glm::vec4& color);

    /// @brief Ustawia tryb wideo (rozmiar okna, fullscreen, Z-buffer).
    void setVideoMode(int width, int height, bool fullscreen = false, bool zBuffer = true);

    /// @brief Ustawia liczbê FPS dla fizyki (fixed update).
    void setFixedUpdateFps(float fps);

    /// @brief Konfiguruje kamerê i rzutowanie.
    void setupView(float farPlane, float nearPlane, float fovDegrees, glm::vec3 cameraPos, glm::vec3 cameraLookAt, glm::vec3 cameraUp = glm::vec3(0, 1, 0));

    /// @brief Aktualizuje kamerê pod¹¿aj¹c¹ za obiektem.
    void updateCameraFollow(const glm::vec3& targetPos, const glm::vec3& offset = glm::vec3(0.0f, 3.0f, 10.0f));

    /// @brief Zwraca obserwatora (kamerê).
    Observer* getObserver() { return observer.get(); }

    /// @brief Konfiguruje oœwietlenie sceny.
    void setupLight(
        const glm::vec3& ambient = glm::vec3(0.2f),
        const glm::vec3& diffuse = glm::vec3(0.8f),
        const glm::vec3& specular = glm::vec3(0.5f),
        const glm::vec3& position = glm::vec3(5.0f, 10.0f, 5.0f),
        bool positional = true);

    /// @brief W³¹cza/wy³¹cza oœwietlenie.
    void toggleLighting();

    /// @brief Sprawdza, czy oœwietlenie jest w³¹czone.
    bool isLightingEnabled() const;

    /// @brief Ustawia callback logiki gry.
    void setUpdateCallback(void (*callback)(float));

    /// @brief Ustawia callback klawiatury.
    void setKeyboardCallback(void (*callback)(unsigned char, int, int));

    /// @brief Dodaje obiekt do silnika.
    void addObject(GameObject* obj) override;

    /// @brief Usuwa obiekt z silnika.
    void removeObject(GameObject* obj) override;

    /// @brief Zwraca pierwszy obiekt danego typu.
    GameObject* getFirstOfType(const std::type_info& type) const override;

    /// @brief Zatrzymuje dzia³anie gry.
    void stop() override;

    /// @brief Zwraca wskaŸnik do interfejsu EngineManager.
    EngineManager* getEngineManager() override;

    /// @brief Zwraca mened¿era tekstur.
    BitmapHandler* getBitmapHandler() override;

    /// @brief Zwraca szerokoœæ okna.
    int getWindowWidth() const { return width; }

    /// @brief Zwraca wysokoœæ okna.
    int getWindowHeight() const { return height; }

    /// @brief Zwraca mapê wejœcia u¿ytkownika.
    InputMap* getInputMap() const { return inputMap.get(); }

    /// @brief Ustawia teksturê t³a dla mapy.
    void setMapBackgroundTexture(GameMap map, GLuint texID);

    /// @brief Ustawia aktywn¹ mapê.
    void selectGameMap(GameMap map);

    /// @brief Zwraca aktywn¹ mapê.
    GameMap getSelectedGameMap() const { return selectedGameMap; }

    /// @brief Zwraca scenê menu.
    MenuScene* getMenuScene() { return menuScene; }

    /// @brief Ustawia scenê menu.
    void setMenuScene(MenuScene* scene) { menuScene = scene; }

    /// @brief Ustawia aktywn¹ scenê gry.
    void setGameScene(GameScene* scene);

    /// @brief Resetuje scenê gry.
    void resetGameScene();

    /// @brief Rozpoczyna grê.
    void startGame();

    /// @brief Przechodzi do stanu Game Over z wynikiem.
    void gameOver(int score);

    /// @brief Restartuje grê.
    void restartGame();

    /// @brief Powraca do menu g³ównego.
    void goToMenu();

    /// @brief Zwraca aktualny stan gry.
    GameState getGameState() const { return currentGameState; }
};
