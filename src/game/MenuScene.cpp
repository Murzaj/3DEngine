#include "game/MenuScene.hpp"
#include "Engine.hpp" 
#include <GL/glew.h> 
#include <GL/freeglut.h> 
#include <iostream> 
#include <fstream>
#include <algorithm>
#include <vector> 

static Engine* g_engineInstanceForMenuActions = nullptr; 


void MenuScene::startGameAction() { 
    if (g_engineInstanceForMenuActions) { 
        g_engineInstanceForMenuActions->startGame(); 
    }
}

void MenuScene::exitGameAction() { 
    if (g_engineInstanceForMenuActions) { 
        g_engineInstanceForMenuActions->stop(); 
    }
}

void MenuScene::restartGameAction() { 
    if (g_engineInstanceForMenuActions) { 
        g_engineInstanceForMenuActions->restartGame(); 
    }
}

void MenuScene::backToMenuAction() { 
    if (g_engineInstanceForMenuActions) { 
        MenuScene* menu = g_engineInstanceForMenuActions->getMenuScene(); 
        if (menu) {
            menu->setActiveViewingHighScores(false);
            menu->setActiveEnteringName(false);
            menu->setGameOver(false);
        }
        g_engineInstanceForMenuActions->goToMenu(); 
    }
}

void MenuScene::openMapSelectionAction() { 
    if (g_engineInstanceForMenuActions && g_engineInstanceForMenuActions->getMenuScene()) { 
        g_engineInstanceForMenuActions->getMenuScene()->setActiveMenu(false); 
        g_engineInstanceForMenuActions->getMenuScene()->setActiveMapSelection(true); 
    }
}

void MenuScene::backToMainMenuActionFromMapSelection() { 
    if (g_engineInstanceForMenuActions && g_engineInstanceForMenuActions->getMenuScene()) { 
        g_engineInstanceForMenuActions->getMenuScene()->setActiveMapSelection(false); 
        g_engineInstanceForMenuActions->getMenuScene()->setActiveMenu(true); 
    }
}

void MenuScene::openHighScoresAction() {
    if (g_engineInstanceForMenuActions && g_engineInstanceForMenuActions->getMenuScene()) { 
        MenuScene* menu = g_engineInstanceForMenuActions->getMenuScene(); 
        menu->setActiveMenu(false); 
        menu->setGameOver(false);
        menu->setActiveEnteringName(false);
        menu->setActiveViewingHighScores(true);
    }
}

void MenuScene::submitNameAction() {
    if (g_engineInstanceForMenuActions && g_engineInstanceForMenuActions->getMenuScene()) {
        MenuScene* menu = g_engineInstanceForMenuActions->getMenuScene();
        if (!menu->currentPlayerName.empty()) {
            menu->addScore(menu->currentPlayerName, menu->currentScoreForEntry);
            menu->saveHighScores();
        }
        menu->setActiveEnteringName(false); 
        menu->menuActive = false;
        menu->mapSelectionActive = false;
        menu->enteringNameActive = false;
        menu->viewingHighScoresActive = false;
        menu->gameOverActive = true;
    }
}



MenuScene::MenuScene(Engine* engine) 
    : enginePtr(engine), menuActive(true), gameOverActive(false), score(0), 
    mapSelectionActive(false), enteringNameActive(false), viewingHighScoresActive(false), 
    currentScoreForEntry(0)
{
    g_engineInstanceForMenuActions = engine; 
    loadHighScores();
}

MenuScene::~MenuScene() {} 



bool MenuScene::init(Initializer* initializer) { 
    setupMenuButtons(); 
    setupGameOverButtons(); 
    setupMapSelectionButtons(); 
    setupHighScoreButtons();
    return true;
}


void MenuScene::setupMenuButtons() { 
    menuButtons.clear(); 
    menuButtons.push_back({ "Rozpocznij Gre",    0.0f,  0.17f, 0.5f, 0.1f, false, startGameAction }); 
    menuButtons.push_back({ "Wybierz Mape",     0.0f,  0.02f,  0.5f, 0.1f, false, openMapSelectionAction }); 
    menuButtons.push_back({ "Tablica Wynikow",  0.0f, -0.13f, 0.5f, 0.1f, false, openHighScoresAction });
    menuButtons.push_back({ "Wyjdz z Gry",       0.0f, -0.30f, 0.5f, 0.1f, false, exitGameAction }); 
}

void MenuScene::setupGameOverButtons() { 
    gameOverButtons.clear(); 
    gameOverButtons.push_back({ "Zagraj Ponownie", 0.0f,  -0.0f, 0.6f, 0.1f, false, restartGameAction }); 
    gameOverButtons.push_back({ "Wyjdz do Menu",   0.0f, -0.1f, 0.6f, 0.1f, false, backToMenuAction }); 
}

void MenuScene::setupMapSelectionButtons() { 
    mapSelectionButtons.clear(); 
    float currentY = 0.4f; 
    float spacing = 0.15f; 
    float buttonWidth = 0.7f; 
    float buttonHeight = 0.1f; 

    mapSelectionButtons.push_back({ "Niebo",    0.0f, currentY, buttonWidth, buttonHeight, false, []() { 
                                        if (g_engineInstanceForMenuActions) g_engineInstanceForMenuActions->selectGameMap(GameMap::NIEBO); 
                                        std::cout << "Wybrano Mape Niebo" << std::endl; 
                                     } }); 
    currentY -= spacing; 
    mapSelectionButtons.push_back({ "Dzungla",  0.0f, currentY, buttonWidth, buttonHeight, false, []() { 
                                        if (g_engineInstanceForMenuActions) g_engineInstanceForMenuActions->selectGameMap(GameMap::DZUNGLA); 
                                        std::cout << "Wybrano Mape Dzungla" << std::endl; 
                                     } }); 
    currentY -= spacing; 
    mapSelectionButtons.push_back({ "Lodowa",   0.0f, currentY, buttonWidth, buttonHeight, false, []() { 
                                        if (g_engineInstanceForMenuActions) g_engineInstanceForMenuActions->selectGameMap(GameMap::LODOWA); 
                                        std::cout << "Wybrano Mape Lodowa" << std::endl; 
                                     } }); 
    currentY -= spacing; 
    mapSelectionButtons.push_back({ "Wulkan",   0.0f, currentY, buttonWidth, buttonHeight, false, []() { 
                                        if (g_engineInstanceForMenuActions) g_engineInstanceForMenuActions->selectGameMap(GameMap::WULKAN); 
                                        std::cout << "Wybrano Mape Wulkan" << std::endl; 
                                     } }); 
    currentY -= spacing; 
    mapSelectionButtons.push_back({ "Pustynia", 0.0f, currentY, buttonWidth, buttonHeight, false, []() { 
                                        if (g_engineInstanceForMenuActions) g_engineInstanceForMenuActions->selectGameMap(GameMap::PUSTYNIA); 
                                        std::cout << "Wybrano Mape Pustynia" << std::endl; 
                                     } }); 

    currentY -= (spacing + 0.1f); 
    mapSelectionButtons.push_back({ "Wroc do Menu", 0.0f, currentY, 0.5f, buttonHeight, false, backToMainMenuActionFromMapSelection }); 
}

void MenuScene::setupHighScoreButtons() {
    highScoreButtons.clear();
    highScoreButtons.push_back({ "Wroc do Menu", 0.0f, -0.8f, 0.5f, 0.1f, false, backToMenuAction });
}


void MenuScene::update(float deltaMs, const InputMap& input, EngineManager* manager) { 
    if (!this->menuActive && !this->gameOverActive && !this->mapSelectionActive && !this->enteringNameActive && !this->viewingHighScoresActive) return; 

    glm::vec2 mousePos = input.getMousePosition(); 
    int screenWidth = enginePtr ? enginePtr->getWindowWidth() : 800; 
    int screenHeight = enginePtr ? enginePtr->getWindowHeight() : 600; 

    float normMouseX = (mousePos.x / static_cast<float>(screenWidth)) * 2.0f - 1.0f; 
    float normMouseY = 1.0f - (mousePos.y / static_cast<float>(screenHeight)) * 2.0f; 

    std::vector<Button>* currentButtons = nullptr; 
    if (this->mapSelectionActive) { 
        currentButtons = &mapSelectionButtons; 
    }
    else if (this->menuActive) { 
        currentButtons = &menuButtons; 
    }
    else if (this->gameOverActive) { 
        currentButtons = &gameOverButtons; 
    }
    else if (this->viewingHighScoresActive) {
        currentButtons = &highScoreButtons;
    }


    if (currentButtons) {
        for (auto& button : *currentButtons) { 
            button.isHovered = button.isMouseOver(normMouseX, normMouseY); 
        }

        if (input.isKeyJustReleased(InputMap::MOUSE_LEFT_CLICK_PSEUDO_KEY)) { 
            for (const auto& button : *currentButtons) { 
                if (button.isHovered && button.action) { 
                    button.action(); 
                    break;
                }
            }
        }
    }

    if (this->enteringNameActive) {
        for (unsigned char key = 'A'; key <= 'Z'; ++key) {
            if (input.isKeyJustPressed(key) || input.isKeyJustPressed(tolower(key))) { 
                if (currentPlayerName.length() < MAX_NAME_LENGTH) {
                    currentPlayerName += key;
                }
            }
        }
        for (unsigned char key = '0'; key <= '9'; ++key) {
            if (input.isKeyJustPressed(key)) { 
                if (currentPlayerName.length() < MAX_NAME_LENGTH) {
                    currentPlayerName += key;
                }
            }
        }
        if (input.isKeyJustPressed(' ')) { 
            if (currentPlayerName.length() < MAX_NAME_LENGTH) {
            }
        }
        if (input.isKeyJustPressed(8)) { 
            if (!currentPlayerName.empty()) {
                currentPlayerName.pop_back();
            }
        }
        if (input.isKeyJustPressed(13)) {
            submitNameAction();
        }
    }
}



void MenuScene::setActiveMenu(bool active) { 
    this->menuActive = active; 
    if (active) {
        this->gameOverActive = false; 
        this->mapSelectionActive = false; 
        this->enteringNameActive = false;
        this->viewingHighScoresActive = false;
    }
}

bool MenuScene::isActiveMenu() const { return this->menuActive; } 

void MenuScene::setGameOver(bool active, int finalScore) { 
    this->currentScoreForEntry = finalScore;
    this->score = finalScore; 

    if (active) {
        this->menuActive = false; 
        this->mapSelectionActive = false; 
        this->viewingHighScoresActive = false;

        if (isHighScore(finalScore)) {
            this->gameOverActive = false;
            this->enteringNameActive = true;
            this->currentPlayerName.clear();
        }
        else {
            this->gameOverActive = true; 
            this->enteringNameActive = false;
        }
    }
    else {
        this->gameOverActive = false;
        this->enteringNameActive = false;
    }
}

bool MenuScene::isGameOver() const { return this->gameOverActive; } 

int MenuScene::getScore() const { return this->score; } 

void MenuScene::setActiveMapSelection(bool active) { 
    this->mapSelectionActive = active; 
    if (active) {
        this->menuActive = false; 
        this->gameOverActive = false; 
        this->enteringNameActive = false;
        this->viewingHighScoresActive = false;
    }
}

bool MenuScene::isActiveMapSelection() const { return this->mapSelectionActive; } 

void MenuScene::setActiveEnteringName(bool active) {
    this->enteringNameActive = active;
    if (active) {
        this->menuActive = false; 
        this->gameOverActive = false; 
        this->mapSelectionActive = false; 
        this->viewingHighScoresActive = false;
    }
}

bool MenuScene::isActiveEnteringName() const {
    return this->enteringNameActive;
}

void MenuScene::setActiveViewingHighScores(bool active) {
    this->viewingHighScoresActive = active;
    if (active) {
        this->menuActive = false; 
        this->gameOverActive = false; 
        this->mapSelectionActive = false; 
        this->enteringNameActive = false;
    }
}

bool MenuScene::isActiveViewingHighScores() const {
    return this->viewingHighScoresActive;
}


void MenuScene::loadHighScores() {
    std::ifstream inFile(highScoreFilename);
    highScores.clear();
    if (inFile.is_open()) {
        ScoreEntry entry;
        while (highScores.size() < MAX_HIGH_SCORES && inFile >> entry.playerName >> entry.score) {
            highScores.push_back(entry);
        }
        inFile.close();
        std::sort(highScores.begin(), highScores.end());
    }
}

void MenuScene::saveHighScores() {
    std::ofstream outFile(highScoreFilename);
    if (outFile.is_open()) {
        for (const auto& entry : highScores) {
            outFile << entry.playerName << " " << entry.score << std::endl;
        }
        outFile.close();
    }
    else {
        std::cerr << "Nie mozna otworzyc pliku do zapisu wynikow: " << highScoreFilename << std::endl;
    }
}

void MenuScene::addScore(const std::string& name, int scoreValue) {
    ScoreEntry newEntry = { name, scoreValue };
    highScores.push_back(newEntry);
    std::sort(highScores.begin(), highScores.end());

    if (highScores.size() > MAX_HIGH_SCORES) {
        highScores.resize(MAX_HIGH_SCORES);
    }
}

bool MenuScene::isHighScore(int scoreValue) const {
    if (highScores.size() < MAX_HIGH_SCORES) {
        return true;
    }
    return scoreValue > highScores.back().score;
}



void MenuScene::draw() { 

}