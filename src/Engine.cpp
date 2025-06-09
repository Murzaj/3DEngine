#include "Engine.hpp"
#include "UpdatableObject.hpp"
#include "Shape3D.hpp"
#include "InputMap.hpp"
#include "Observer.hpp"
#include "SoundHandler.hpp"
#include "BitmapHandler.hpp"
#include "game/GameScene.hpp"
#include "SphereShape3D.hpp"
#include "game/MenuScene.hpp"

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <iomanip> 
#include <sstream> 


Engine* Engine::instance = nullptr;

Engine::Engine() :
    name("3D Engine"),
    width(800),
    height(600),
    fixedUpdateMs(1000.0f / 60.0f),
    fullscreen(false),
    displayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE),
    farPlane(1000.0f),
    nearPlane(0.1f),
    fov(glm::radians(75.0f)),
    running(true),
    lightingEnabled(true),
    keyboardCallback(nullptr),
    updateCallback(nullptr),
    currentGameState(GameState::MENU),
    nieboBackgroundTextureID(0), 
    dzunglaBackgroundTextureID(0),
    lodowaBackgroundTextureID(0),
    wulkanBackgroundTextureID(0),
    pustyniaBackgroundTextureID(0),
    selectedGameMap(GameMap::NIEBO)


{
    if (instance != nullptr) {
        std::cerr << "Instancja silnika juz istnieje!" << std::endl;

    }
    instance = this;
    std::cout << "Wywolano konstruktor silnika." << std::endl;


    inputMap = std::make_unique<InputMap>();
    bitmapHandler = std::make_unique<BitmapHandler>();
    soundHandler = std::make_unique<SoundHandler>();
}


Engine::~Engine() {
    std::cout << "Rozpoczeto destruktor silnika." << std::endl;
    cleanupObjects();
    instance = nullptr;
    std::cout << "Zakonczono destruktor silnika." << std::endl;
}



bool Engine::initialize(int* argc, char* argv[]) {
    std::cout << "Inicjalizacja silnika..." << std::endl;
    glutInit(argc, argv);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(displayMode);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(name.c_str());

    if (fullscreen) {
        glutFullScreen();
    }

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cerr << "glewInit nie powiodlo sie: " << glewGetErrorString(err) << std::endl;
        return false;
    }
    std::cout << "Zainicjalizowano GLEW." << std::endl;



    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);


    if (lightingEnabled) {
        glEnable(GL_LIGHTING);
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_LIGHT0);
        glShadeModel(GL_SMOOTH);
    }
    else {
        glDisable(GL_LIGHTING);
    }

    glEnable(GL_TEXTURE_2D);

    setClearColor(glm::vec4(0.5f, 0.7f, 1.0f, 1.0f));


    onReshape(width, height);


    if (!observer && currentGameState != GameState::MENU && currentGameState != GameState::GAME_OVER) {
        std::cout << "Obserwator nieustawiony podczas inicjalizacji, tworzenie domyslnego." << std::endl;
        observer = std::make_unique<Observer>(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0));
    }


    std::cout << "Inicjalizacja silnika zakonczona.." << std::endl;
    return true;
}

void Engine::run() {
    std::cout << "Wywo³ano Engine run()." << std::endl;
    if (currentGameState != GameState::MENU && currentGameState != GameState::GAME_OVER && !observer) {
        std::cerr << "Kamera (Obserwator) nieustawiona dla stanu IN_GAME." << std::endl;
        return;
    }
    if (!inputMap) {
        std::cerr << "Nie zainicjalizowano InputMap." << std::endl;
        return;
    }
    if (!bitmapHandler) {
        std::cerr << "Nie zainicjalizowano BitmapHandler." << std::endl;
        return;
    }
    if (!menuScene) {
        std::cerr << "MenuScene nie jest ustawione!" << std::endl;
        return;
    }


    prepareObjects();
    prepareCallbacks();
    setupTimer();

    std::cout << "Rozpoczynanie glownej petli..." << std::endl;
    running = true;
    mainLoopInternal();
    std::cout << "Zakonczono glowna petle." << std::endl;

}

void Engine::mainLoop() {
    if (running) {
        std::cout << "Wywolano Engine::mainLoop(), wejscie do glownej petli GLUT." << std::endl;
        mainLoopInternal();
    }
    else {
        std::cout << "Wywolano Engine::mainLoop(), ale silnik nie jest w stanie uruchamialnym." << std::endl;
    }
}


void Engine::mainLoopInternal() {
    glutMainLoop();
}


void Engine::stop() {
    std::cout << "Wywolano Engine stop()." << std::endl;
    if (running) {
        running = false;
        if (gameScene) {
            removeObject(gameScene); 
            delete gameScene;
            gameScene = nullptr;
        }

        glutLeaveMainLoop();
        std::cout << "wyjscie z glownej petli GLUT" << std::endl;
    }
}


void Engine::setWindowName(const std::string& title) {
    name = title;
    if (glutGetWindow()) {
        glutSetWindowTitle(name.c_str());
    }
}

void Engine::setClearColor(const glm::vec4& color) {
    glClearColor(color.r, color.g, color.b, color.a);
}

void Engine::setVideoMode(int w, int h, bool fs, bool zBuf) {
    width = w;
    height = h;
    fullscreen = fs;
    displayMode = GLUT_RGB | GLUT_DOUBLE | GLUT_MULTISAMPLE;
    if (zBuf) {
        displayMode |= GLUT_DEPTH;
    }
    if (glutGetWindow()) {
        std::cout << "Ostrzezenie silnika: Zmiana trybu wideo po inicjalizacji" << std::endl;
        glutReshapeWindow(width, height);
        if (fullscreen) glutFullScreen();
    }
}

void Engine::setFixedUpdateFps(float fps) {
    if (fps > 0) {
        fixedUpdateMs = 1000.0f / fps;
    }
    else {
        fixedUpdateMs = 0;
    }
}

void Engine::setupView(float fPlane, float nPlane, float fovDeg, glm::vec3 camPos, glm::vec3 camTarget, glm::vec3 camUp) {
    farPlane = fPlane;
    nearPlane = nPlane;
    fov = glm::radians(fovDeg);


    observer = std::make_unique<Observer>(camPos, camTarget, camUp);

    onReshape(width, height);
}

void Engine::updateCameraFollow(const glm::vec3& targetPos, const glm::vec3& offset) {
    if (observer) {
        glm::vec3 cameraPos = targetPos + offset;
        observer->lookAt(cameraPos, targetPos);
    }
}

void Engine::setupLight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const glm::vec3& position, bool positional) {
    if (!lightingEnabled) return;

    glEnable(GL_LIGHT0);

    GLfloat amb[] = { ambient.r, ambient.g, ambient.b, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);


    GLfloat diff[] = { diffuse.r, diffuse.g, diffuse.b, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);

    GLfloat spec[] = { specular.r, specular.g, specular.b, 1.0f };
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec);


    GLfloat lightPosW[] = { position.x, position.y, position.z, positional ? 1.0f : 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosW);


    if (positional) {
        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0f);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0f);
    }

}


void Engine::toggleLighting() {
    lightingEnabled = !lightingEnabled;
    if (lightingEnabled) {
        glEnable(GL_LIGHTING);
    }
    else {
        glDisable(GL_LIGHTING);
    }
}

bool Engine::isLightingEnabled() const {
    return lightingEnabled;
}

void Engine::setUpdateCallback(void (*callback)(float)) {
    updateCallback = callback;
}

void Engine::setKeyboardCallback(void (*callback)(unsigned char, int, int)) {
    keyboardCallback = callback;
}



EngineManager* Engine::getEngineManager() { return this; }
BitmapHandler* Engine::getBitmapHandler() { return bitmapHandler.get(); }

void Engine::setMapBackgroundTexture(GameMap map, GLuint texID) {
    switch (map) {
    case GameMap::NIEBO:
        nieboBackgroundTextureID = texID;
        std::cout << "Tekstura tla dla Mapy Niebo ustawiona na ID: " << texID << std::endl;
        break;
    case GameMap::DZUNGLA:
        dzunglaBackgroundTextureID = texID;
        std::cout << "Tekstura tla dla Mapy Dzsungla ustawiona na ID: " << texID << std::endl;
        break;
    case GameMap::LODOWA:
        lodowaBackgroundTextureID = texID;
        std::cout << "Tekstura tla dla Mapy Lodowa ustawiona na ID: " << texID << std::endl;
        break;
    case GameMap::WULKAN:
        wulkanBackgroundTextureID = texID;
        std::cout << "Tekstura tla dla Mapy Wulkan ustawiona na ID: " << texID << std::endl;
        break;
    case GameMap::PUSTYNIA:
        pustyniaBackgroundTextureID = texID;
        std::cout << "Tekstura tla dla Mapy Pustynia ustawiona na ID: " << texID << std::endl;
        break;
    default:
        std::cerr << "Nieznany typ mapy przy ustawianiu tekstury tla." << std::endl;
        break;
    }
}

void Engine::selectGameMap(GameMap map) {
    selectedGameMap = map;
    std::cout << "Wybrano mape: " << static_cast<int>(map) << std::endl;
}

void Engine::addObject(GameObject* obj) {
    if (!obj) {
        
        return;
    }

    if (auto ms = dynamic_cast<MenuScene*>(obj)) {
        if (menuScene == nullptr) {
            menuScene = ms;
        }
        else if (menuScene != ms) { 
            std::cerr << "Proba dodania drugiej instancji MenuScene. Zachowuje poprzednia." << std::endl;
            delete obj; 
            return;
        }
    }



    if (!obj->init(this)) {
        return;
    }

   
    if (!obj->init(this)) {
        std::cout << "Engine::addObject: Inicjalizacja obiektu (" << obj << ") nie powiodla sie." << std::endl;
        return;
    }

    bool alreadyExists = false;
    for (const auto& existingObj : objects) {
        if (existingObj == obj) {
            alreadyExists = true;
            break;
        }
    }
    if (alreadyExists && obj == menuScene) { 
    }
    else if (!alreadyExists) {
        objects.push_back(obj);
        if (auto shapePtr = dynamic_cast<Shape3D*>(obj)) {
            shapes.push_back(shapePtr);
        }
        if (auto updatablePtr = dynamic_cast<UpdatableObject*>(obj)) {
            if (dynamic_cast<MenuScene*>(obj) == nullptr) {
                updatables.push_back(updatablePtr);
            }
        }
    }
}


void Engine::removeObject(GameObject* obj) {
    if (!obj) return;

    if (obj == gameScene) {
        gameScene = nullptr;
    }

    bool alreadyMarked = false;
    for (const auto& item : cleanupQueue) {
        if (item == obj) {
            alreadyMarked = true;
            break;
        }
    }
    if (!alreadyMarked) {
        cleanupQueue.push_back(obj);
    }
}


GameObject* Engine::getFirstOfType(const std::type_info& type) const {
    for (GameObject* obj : objects) {
        if (obj && typeid(*obj) == type) {
            return obj;
        }
    }
    if (typeid(MenuScene) == type && menuScene) return menuScene;
    return nullptr;
}




void Engine::prepareObjects() {
}


void Engine::processCleanupQueue() {
    if (cleanupQueue.empty()) {
        return;
    }
  

    std::vector<GameObject*> currentQueueIteration = cleanupQueue;
    cleanupQueue.clear(); 

    for (GameObject* objToRemove : currentQueueIteration) {
        if (!objToRemove) {
            continue;
        }


        if (auto shapePtr = dynamic_cast<Shape3D*>(objToRemove)) {
            auto original_shapes_size = shapes.size();

            auto it = std::remove(shapes.begin(), shapes.end(), shapePtr);
            bool removed_from_shapes = (it != shapes.end());
            if (removed_from_shapes) {
                shapes.erase(it, shapes.end());
            }
            else {
            }
        }
        else {
        }

        if (auto updatablePtr = dynamic_cast<UpdatableObject*>(objToRemove)) {
            if (updatablePtr != menuScene) { 
                auto original_updatables_size = updatables.size();
                auto it = std::remove(updatables.begin(), updatables.end(), updatablePtr);
                bool removed_from_updatables = (it != updatables.end());
                if (removed_from_updatables) {
                    updatables.erase(it, updatables.end());
                }
                else {
                }
            }
        }

        auto original_objects_size = objects.size();
        auto it_obj = std::remove(objects.begin(), objects.end(), objToRemove);
        bool removed_from_objects = (it_obj != objects.end());
        if (removed_from_objects) {
            objects.erase(it_obj, objects.end());
        }
        else {
        }


        if (objToRemove == menuScene && running) {
        }
        else {
            delete objToRemove; 
        }
    }

}


void Engine::cleanupObjects() {
    processCleanupQueue();

    if (gameScene) {
        removeObject(gameScene); 

        auto it_gs_obj = std::find(objects.begin(), objects.end(), static_cast<GameObject*>(gameScene));
        if (it_gs_obj != objects.end()) {
            objects.erase(it_gs_obj);
        }
        auto it_gs_upd = std::find(updatables.begin(), updatables.end(), static_cast<UpdatableObject*>(gameScene));
        if (it_gs_upd != updatables.end()) {
            updatables.erase(it_gs_upd);
        }
        delete gameScene;
        gameScene = nullptr;
    }


    std::vector<GameObject*> remainingObjects = objects; 
    for (GameObject* obj : remainingObjects) {
        if (obj && obj != menuScene) { 
            removeObject(obj); 
        }
    }
    processCleanupQueue(); 

    if (menuScene && !running) { 
        delete menuScene;
        menuScene = nullptr;
    }
    else if (menuScene) {
    }


    objects.clear();
    shapes.clear();
    updatables.clear();

}


void Engine::prepareCallbacks() {
    glutDisplayFunc(displayWrapper);
    glutReshapeFunc(reshapeWrapper);
    glutKeyboardFunc(keyboardWrapper);
    glutKeyboardUpFunc(keyboardUpWrapper);
    glutSpecialFunc(specialWrapper);
    glutSpecialUpFunc(specialUpWrapper);
    glutMotionFunc(motionWrapper);
    glutPassiveMotionFunc(passiveMotionWrapper);
    glutMouseWheelFunc(mouseWheelWrapper);
    glutMouseFunc(mouseFuncWrapper);
    glutCloseFunc(closeWrapper);


    glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);

}


void Engine::setupTimer() {
    if (fixedUpdateMs > 0 && running) {
        glutTimerFunc(static_cast<unsigned int>(fixedUpdateMs), fixedUpdateWrapper, 0);
    }
}


void Engine::fixedUpdate() {
    if (!running) return;

    processCleanupQueue();


    if (updateCallback) {
        updateCallback(fixedUpdateMs);
    }


    if (inputMap) {
        switch (currentGameState) {
        case GameState::MENU:
        case GameState::GAME_OVER:
            if (menuScene) {
                menuScene->update(fixedUpdateMs, *inputMap, this);
            }
            break;
        case GameState::IN_GAME:
            if (gameScene) { 
                gameScene->update(fixedUpdateMs, *inputMap, this);
            }

            for (auto updatable : updatables) {
                if (updatable && updatable != static_cast<UpdatableObject*>(menuScene) && updatable != static_cast<UpdatableObject*>(gameScene)) {
                    updatable->update(fixedUpdateMs, *inputMap, this);
                }
            }
            break;
        }
    }
    else {
    }


    if (inputMap) {
        inputMap->updateFrameState();
    }

    setupTimer();
    glutPostRedisplay();
}


void Engine::display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLuint backgroundToUse = 0;

    switch (currentGameState) {
    case GameState::MENU:
    case GameState::GAME_OVER:
        drawMenuUI();
        break;
    case GameState::IN_GAME:
        if (!observer) return;



        switch (selectedGameMap) {
        case GameMap::NIEBO:
            backgroundToUse = nieboBackgroundTextureID;
            break;
        case GameMap::DZUNGLA:
            backgroundToUse = dzunglaBackgroundTextureID;
            break;
        case GameMap::LODOWA:
            backgroundToUse = lodowaBackgroundTextureID;
            break;
        case GameMap::WULKAN:
            backgroundToUse = wulkanBackgroundTextureID;
            break;
        case GameMap::PUSTYNIA:
            backgroundToUse = pustyniaBackgroundTextureID;
            break;
        default:
            backgroundToUse = nieboBackgroundTextureID; 
            break;
        }

        if (backgroundToUse > 0) {

            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadIdentity();
            gluOrtho2D(0, width, 0, height);

            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();

            glDisable(GL_LIGHTING);
            glDisable(GL_DEPTH_TEST);
            glEnable(GL_TEXTURE_2D);

            glBindTexture(GL_TEXTURE_2D, backgroundToUse);
            glColor3f(1.0f, 1.0f, 1.0f);

            glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
            glTexCoord2f(1.0f, 0.0f); glVertex2f(width, 0.0f);
            glTexCoord2f(1.0f, 1.0f); glVertex2f(width, height);
            glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, height);
            glEnd();

            glBindTexture(GL_TEXTURE_2D, 0);
            glEnable(GL_DEPTH_TEST);
            glPopMatrix();
            glMatrixMode(GL_PROJECTION);
            glPopMatrix();
        }

        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(glm::value_ptr(projection));

        glMatrixMode(GL_MODELVIEW);
        const glm::mat4 viewMatrix = observer->getTransform();
        glLoadMatrixf(glm::value_ptr(viewMatrix));

        if (lightingEnabled) {
            glEnable(GL_LIGHTING);
        }
        else {
            glDisable(GL_LIGHTING);
        }

        for (auto shape : shapes) {
            if (shape) {
                bool isMenuShape = false;
                if (menuScene && menuScene->getShape() == shape) isMenuShape = true; 

                if (!isMenuShape || currentGameState == GameState::IN_GAME) {
                    if (shape != dynamic_cast<Shape3D*>(menuScene)) {
                        shape->draw(viewMatrix);
                    }
                }
            }
        }
        if (gameScene) {
            int currentScore = gameScene->getScore();
            std::string scoreStr = "Punkty: " + std::to_string(currentScore);
            drawText(10.0f,
                static_cast<float>(height) - 20.0f,
                scoreStr,
                GLUT_BITMAP_HELVETICA_18,
                1.0f, 1.0f, 1.0f); 
        }
        break;
    }

    glutSwapBuffers();
}



void Engine::drawText(float x, float y, const std::string& text, void* font, float r, float g, float b, float makeBoldFactor) { 
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);

    glColor3f(r, g, b);


    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(font, c);
    }

    if (makeBoldFactor > 1.1f) {
        glRasterPos2f(x + 1.0f, y);
        for (char c : text) {
            glutBitmapCharacter(font, c);
        }
    }

    glEnable(GL_DEPTH_TEST);
    glPopMatrix(); 
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void Engine::drawMenuUI() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, static_cast<double>(width), 0.0, static_cast<double>(height));

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);


    GLuint bgTextureID = 0;
    if (bitmapHandler) {
        bgTextureID = bitmapHandler->getBitmap("menuBackground");
    }
    if (bgTextureID > 0) {
        glBindTexture(GL_TEXTURE_2D, bgTextureID);
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(static_cast<float>(width), 0.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(static_cast<float>(width), static_cast<float>(height));
        glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, static_cast<float>(height));
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    glDisable(GL_TEXTURE_2D);

    if (menuScene) {
        if (menuScene->isActiveMapSelection()) {
            const auto& buttons = menuScene->getMapSelectionButtons();
            GameMap selMap = getSelectedGameMap();

            for (const auto& button : buttons) {
                float btnPixelX = (button.x + 1.0f) / 2.0f * width;
                float btnPixelY = (button.y + 1.0f) / 2.0f * height;
                float textWidthVal = static_cast<float>(
                    glutBitmapLength(GLUT_BITMAP_HELVETICA_18,
                        (const unsigned char*)button.text.c_str()));
                float textDrawX = btnPixelX - textWidthVal / 2.0f;
                float textDrawY = btnPixelY - (glutBitmapHeight(GLUT_BITMAP_HELVETICA_18) / 2.0f);


                bool isSelected = false;
                if (button.text == "Niebo" && selMap == GameMap::NIEBO)    isSelected = true;
                if (button.text == "Dzungla" && selMap == GameMap::DZUNGLA) isSelected = true;
                if (button.text == "Lodowa" && selMap == GameMap::LODOWA)  isSelected = true;
                if (button.text == "Wulkan" && selMap == GameMap::WULKAN)  isSelected = true;
                if (button.text == "Pustynia" && selMap == GameMap::PUSTYNIA) isSelected = true;

                float r, g, b;
                if (button.isHovered) {
                    r = 1.0f; g = 1.0f; b = 0.0f;           
                }
                else if (isSelected) {
                    r = 1.0f; g = 0.5f; b = 0.0f;           
                }
                else {
                    r = 0.0f; g = 0.0f; b = 0.0f;           
                }

                drawText(textDrawX, textDrawY, button.text,
                    GLUT_BITMAP_HELVETICA_18, r, g, b);
            }
        }
        else if (menuScene->isActiveMenu()) {
            const auto& buttons = menuScene->getMenuButtons();
            for (const auto& button : buttons) {
                float btnPixelX = (button.x + 1.0f) / 2.0f * width;
                float btnPixelY = (button.y + 1.0f) / 2.0f * height;
                float textWidthVal = static_cast<float>(
                    glutBitmapLength(GLUT_BITMAP_HELVETICA_18,
                        (const unsigned char*)button.text.c_str()));
                float textDrawX = btnPixelX - textWidthVal / 2.0f;
                float textDrawY = btnPixelY - (glutBitmapHeight(GLUT_BITMAP_HELVETICA_18) / 2.0f);
                float r = 0.0f, g = 0.0f, b = 0.0f;

                if (button.text == "Wyjdz z Gry") {
                    if (button.isHovered) {
                        r = 1.0f; g = 1.0f; b = 0.0f;
                    }
                    else {
                        r = 1.0f; g = 0.0f; b = 0.0f;
                    }
                }
                else {
                    if (button.isHovered) {
                        r = 1.0f; g = 1.0f; b = 0.0f;
                    }
                    else {
                        r = 0.0f; g = 0.0f; b = 0.0f;
                    }
                }

                drawText(textDrawX, textDrawY, button.text,
                    GLUT_BITMAP_HELVETICA_18, r, g, b);
            }
        }
        else if (menuScene->isGameOver()) {
            std::string gameOverText = "GAME OVER";
            float goTextWidth = static_cast<float>(
                glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24,
                    (const unsigned char*)gameOverText.c_str()));
            drawText((width - goTextWidth) / 2.0f, height * 0.7f,
                gameOverText, GLUT_BITMAP_TIMES_ROMAN_24, 1.0f, 0.0f, 0.0f, 1.5f);

            std::ostringstream scoreStream;
            scoreStream << "Wynik: " << menuScene->getScore();
            std::string scoreText = scoreStream.str();
            float scoreTextWidth = static_cast<float>(
                glutBitmapLength(GLUT_BITMAP_HELVETICA_18,
                    (const unsigned char*)scoreText.c_str()));
            drawText((width - scoreTextWidth) / 2.0f, height * 0.55f,
                scoreText, GLUT_BITMAP_HELVETICA_18, 0.0f, 0.0f, 0.0f);

            const auto& buttons = menuScene->getGameOverButtons();
            for (const auto& button : buttons) {
                float btnPixelX = (button.x + 1.0f) / 2.0f * width;
                float btnPixelY = (button.y + 1.0f) / 2.0f * height;
                float textWidthVal = static_cast<float>(
                    glutBitmapLength(GLUT_BITMAP_HELVETICA_18,
                        (const unsigned char*)button.text.c_str()));
                float textDrawX = btnPixelX - textWidthVal / 2.0f;
                float textDrawY = btnPixelY - (glutBitmapHeight(GLUT_BITMAP_HELVETICA_18) / 2.0f);
                drawText(textDrawX, textDrawY, button.text,
                    GLUT_BITMAP_HELVETICA_18,
                    button.isHovered ? 1.0f : 0.0f,
                    button.isHovered ? 1.0f : 0.0f,
                    button.isHovered ? 0.0f : 0.0f);
            }
        }
        else if (menuScene->isActiveEnteringName()) {
            std::ostringstream scoreStream;
            scoreStream << "Twoj Wynik: " << menuScene->getCurrentScoreForEntry();
            std::string scoreText = scoreStream.str();
            float scoreTextWidth = static_cast<float>(
                glutBitmapLength(GLUT_BITMAP_HELVETICA_18,
                    (const unsigned char*)scoreText.c_str()));
            drawText((width - scoreTextWidth) / 2.0f, height * 0.65f,
                scoreText, GLUT_BITMAP_HELVETICA_18, 0.0f, 0.0f, 0.0f);

            std::string promptText = "Wpisz swoj nick (max " +
                std::to_string(MenuScene::MAX_NAME_LENGTH) + " znakow):";
            float promptWidth = static_cast<float>(
                glutBitmapLength(GLUT_BITMAP_HELVETICA_18,
                    (const unsigned char*)promptText.c_str()));
            drawText((width - promptWidth) / 2.0f, height * 0.5f,
                promptText, GLUT_BITMAP_HELVETICA_18, 0.0f, 0.0f, 0.0f);

            std::string nameToDraw = menuScene->getCurrentPlayerName() + "_";
            float nameWidth = static_cast<float>(
                glutBitmapLength(GLUT_BITMAP_HELVETICA_18,
                    (const unsigned char*)nameToDraw.c_str()));
            drawText((width - nameWidth) / 2.0f, height * 0.4f,
                nameToDraw, GLUT_BITMAP_HELVETICA_18, 0.1f, 0.1f, 0.8f);

            std::string continueText = "Nacisnij ENTER aby zapisac";
            float continueWidth = static_cast<float>(
                glutBitmapLength(GLUT_BITMAP_HELVETICA_18,
                    (const unsigned char*)continueText.c_str()));
            drawText((width - continueWidth) / 2.0f, height * 0.25f,
                continueText, GLUT_BITMAP_HELVETICA_18, 0.0f, 0.0f, 0.0f);
        }
        else if (menuScene->isActiveViewingHighScores()) {
            std::string titleText = "TABLICA WYNIKOW";
            float titleWidth = static_cast<float>(
                glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24,
                    (const unsigned char*)titleText.c_str()));
            drawText((width - titleWidth) / 2.0f, height * 0.85f,
                titleText, GLUT_BITMAP_TIMES_ROMAN_24, 0.0f, 0.0f, 0.0f);

            const auto& scores = menuScene->getHighScores();
            float currentY = height * 0.75f;
            int rank = 1;
            float lineHeight = static_cast<float>(
                glutBitmapHeight(GLUT_BITMAP_HELVETICA_18)) + 10.0f;

            for (const auto& scoreEntry : scores) {
                std::ostringstream scoreLineStream;
                scoreLineStream << std::setw(2) << std::right << rank << ". "
                    << std::setw(MenuScene::MAX_NAME_LENGTH + 2) << std::left << scoreEntry.playerName
                    << std::setw(8) << std::right << scoreEntry.score;
                std::string scoreLine = scoreLineStream.str();

                float lineWidth = static_cast<float>(
                    glutBitmapLength(GLUT_BITMAP_HELVETICA_18,
                        (const unsigned char*)scoreLine.c_str()));
                drawText((width - lineWidth) / 2.0f, currentY,
                    scoreLine, GLUT_BITMAP_HELVETICA_18, 0.0f, 0.0f, 0.0f);
                currentY -= lineHeight;
                rank++;
                if (rank > 10) break;
            }
            if (scores.empty()) {
                std::string noScoresText = "Brak zapisanych wynikow.";
                float noScoresWidth = static_cast<float>(
                    glutBitmapLength(GLUT_BITMAP_HELVETICA_18,
                        (const unsigned char*)noScoresText.c_str()));
                drawText((width - noScoresWidth) / 2.0f, currentY,
                    noScoresText, GLUT_BITMAP_HELVETICA_18, 0.0f, 0.0f, 0.0f);
            }

            const auto& buttons = menuScene->getHighScoreButtons();
            for (const auto& button : buttons) {
                float btnPixelX = (button.x + 1.0f) / 2.0f * width;
                float btnPixelY = (button.y + 1.0f) / 2.0f * height;
                float textWidthVal = static_cast<float>(
                    glutBitmapLength(GLUT_BITMAP_HELVETICA_18,
                        (const unsigned char*)button.text.c_str()));
                float textDrawX = btnPixelX - textWidthVal / 2.0f;
                float textDrawY = btnPixelY - (glutBitmapHeight(GLUT_BITMAP_HELVETICA_18) / 2.0f);
                drawText(textDrawX, textDrawY, button.text,
                    GLUT_BITMAP_HELVETICA_18,
                    button.isHovered ? 1.0f : 0.0f,
                    button.isHovered ? 1.0f : 0.0f,
                    button.isHovered ? 0.0f : 0.0f);
            }
        }
    }

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}


void Engine::onReshape(int w, int h) {
    width = w;
    height = h;
    if (height == 0) height = 1;
    glViewport(0, 0, width, height);

    if (currentGameState == GameState::IN_GAME || observer) { 
        projection = glm::perspective(fov, static_cast<float>(width) / static_cast<float>(height), nearPlane, farPlane);
        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(glm::value_ptr(projection));
        glMatrixMode(GL_MODELVIEW);
    }
}

void Engine::onKeyboard(unsigned char key, int x, int y) { 
    if (inputMap) inputMap->setKeyDown(key); 


    if (keyboardCallback) { 
        keyboardCallback(key, x, y); 
    }

    if (key == 27) {
        if (currentGameState == GameState::IN_GAME) { 
            if (menuScene && menuScene->isActiveMapSelection()) { 
                menuScene->setActiveMapSelection(false); 
                menuScene->setActiveMenu(true); 
            }
            else if (menuScene && menuScene->isActiveEnteringName()) { 
                menuScene->setActiveEnteringName(false); 
                menuScene->setActiveMenu(true); 

            }
            else if (menuScene && menuScene->isActiveViewingHighScores()) { 
                menuScene->setActiveViewingHighScores(false); 
                menuScene->setActiveMenu(true); 
            }
            else {
                goToMenu(); 
            }
        }
        else if (currentGameState == GameState::MENU || currentGameState == GameState::GAME_OVER) { 
            if (menuScene && menuScene->isActiveMapSelection()) { 
                menuScene->setActiveMapSelection(false); 
                menuScene->setActiveMenu(true); 
            }
            else if (menuScene && menuScene->isActiveViewingHighScores()) { 
                menuScene->setActiveViewingHighScores(false); 
                menuScene->setActiveMenu(true); 
            }

            else if (currentGameState == GameState::GAME_OVER && menuScene && !menuScene->isActiveEnteringName()) {
                this->goToMenu(); 
            }
            else {
                stop(); 
            }
        }
    }
}


void Engine::onKeyboardUp(unsigned char key, int x, int y) {
    if (inputMap) inputMap->setKeyUp(key);
}

void Engine::onSpecial(int key, int x, int y) {
}

void Engine::onSpecialUp(int key, int x, int y) {
}

void Engine::onMotion(int x, int y) {
    if (inputMap) {
        inputMap->setMousePosition(x, y);
    }
}

void Engine::onPassiveMotion(int x, int y) {
    if (inputMap) {
        inputMap->setMousePosition(x, y);
    }
}


void Engine::onMouseFunc(int button, int state, int x, int y) {
    if (inputMap) {
        inputMap->setMousePosition(x, y); 

        if (button == GLUT_LEFT_BUTTON) {
            if (state == GLUT_DOWN) {
                inputMap->setKeyDown(InputMap::MOUSE_LEFT_CLICK_PSEUDO_KEY);
                inputMap->setLeftClickDown();
            }
            else if (state == GLUT_UP) {
                inputMap->setKeyUp(InputMap::MOUSE_LEFT_CLICK_PSEUDO_KEY);
                inputMap->setLeftClickUp();
            }
        }
        else if (button == GLUT_RIGHT_BUTTON) {
            if (state == GLUT_DOWN) inputMap->setRightClickDown();
            else inputMap->setRightClickUp();
        }
        else if (button == GLUT_MIDDLE_BUTTON) {
            if (state == GLUT_DOWN) inputMap->setMiddleClickDown();
            else inputMap->setMiddleClickUp();
        }
    }
}

void Engine::onMouseWheel(int wheel, int direction, int x, int y) {
    if (inputMap) {
        inputMap->setWheelDirection(direction);
    }
}

void Engine::setGameScene(GameScene* scene) {
    if (gameScene && gameScene != scene) {
        removeObject(gameScene); 
        delete gameScene;
    }
    gameScene = scene;
    if (gameScene) {
        addObject(gameScene); 
    }
}

void Engine::resetGameScene() {
    if (gameScene) { 
        removeObject(gameScene);
        gameScene = nullptr;
    }

    GLuint spikeTex = bitmapHandler->getBitmap("spikeTex");
    if (spikeTex == 0) {
        spikeTex = bitmapHandler->loadBitmap("spikeTex", "spike.jpg");
        if (spikeTex == 0) {
            std::cerr << "Nie udalo sie zaladowac tekstury kolca podczas resetu." << std::endl;
        }
    }

    auto playerSphere = new SphereShape3D(glm::vec3(0.3f, 0.5f, 1.0f), 0.5f, 24, 24);
    

    GameScene* newGameScene = new GameScene(playerSphere, 0.5f, spikeTex);
    setGameScene(newGameScene);
}


void Engine::startGame() {
    if (currentGameState == GameState::MENU || currentGameState == GameState::GAME_OVER) {
        if (soundHandler) { 
            soundHandler->stopAllSounds(); 
            soundHandler->playSound("background_music"); 
        }
        resetGameScene(); 
        currentGameState = GameState::IN_GAME;
        if (menuScene) menuScene->setActiveMenu(false);
        if (menuScene) menuScene->setGameOver(false);

        glutSetCursor(GLUT_CURSOR_INHERIT);
        if (isLightingEnabled()) { 
            glEnable(GL_LIGHTING);
        }
        if (!observer) {
            setupView(500.0f, 0.1f, 75.0f, glm::vec3(0, 5, 10), glm::vec3(0, 0, 0));
        }
    }
}

void Engine::gameOver(int score) { 
    currentGameState = GameState::GAME_OVER; 
    if (soundHandler) { 
        soundHandler->stopSound("background_music");
        soundHandler->playSound("collision_sound");
    }
    if (menuScene) { 
        menuScene->setGameOver(true, score); 
    }

    glutSetCursor(GLUT_CURSOR_LEFT_ARROW); 
    glDisable(GL_LIGHTING); 
}

void Engine::restartGame() {
    if (soundHandler) {
        soundHandler->stopAllSounds(); 
    }
    startGame();
}

void Engine::goToMenu() {
    if (gameScene) {
        removeObject(gameScene);
        gameScene = nullptr;
    }
    if (soundHandler) { 
        soundHandler->stopSound("background_music");
    }
    currentGameState = GameState::MENU;
    if (menuScene) menuScene->setActiveMenu(true);
    if (menuScene) menuScene->setGameOver(false);
    glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
    glDisable(GL_LIGHTING);
}