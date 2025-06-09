#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>

#include "Engine.hpp"
#include "SoundHandler.hpp"
#include "SphereShape3D.hpp"
#include "game/GameScene.hpp"
#include "game/MenuScene.hpp"
#include "BitmapHandler.hpp"
#include <filesystem>

int main(int argc, char** argv)
{
    std::cout << "Uruchamianie aplikacji..." << std::endl;

    Engine engine;
    engine.setWindowName("Kulen Machen");
    engine.setVideoMode(1024, 768, false, true);
    engine.setFixedUpdateFps(60.0f);
    engine.setClearColor(glm::vec4(0.1f, 0.05f, 0.15f, 1.0f));

    if (!engine.initialize(&argc, argv)) {
        std::cerr << "Nie udalo sie zainicjalizowac silnika." << std::endl;
        return 1;
    }

    BitmapHandler* bmpHandler = engine.getBitmapHandler();
    if (!bmpHandler) {
        std::cerr << "Nie udalo sie uzyskac BitmapHandler z silnika." << std::endl;
        return 1;
    }
    try {
        std::cout << "Biezacy katalog roboczy:  " << std::filesystem::current_path() << std::endl;
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Blad pobierania biezacej sciezki: " << e.what() << std::endl;
    }
   
    SoundHandler* soundHandler = engine.getSoundHandler(); 
    if (!soundHandler) { 
        std::cerr << "Nie udalo sie uzyskac SoundHandler z silnika." << std::endl; 
        return 1; 
    }
    if (!soundHandler->loadSound("background_music", "background_music.wav", true)) {
        std::cerr << "Nie udalo sie zaladowac muzyki tla: background_music.wav" << std::endl;
    }
    if (!soundHandler->loadSound("collision_sound", "collision_sound.wav", false)) { 
        std::cerr << "Nie udalo sie zaladowac dzwieku kolizji: collision_sound.wav" << std::endl;
    }

    GLuint spikeTex = bmpHandler->loadBitmap("spikeTex", "spike.jpg");
    if (spikeTex == 0) {
        std::cerr << "Nie udalo sie zaladowac tekstury kolca: spike.jpg" << std::endl;
    }
    else {
        std::cout << "Zaladowano teksture kolca ID: " << spikeTex << std::endl;
    }

    GLuint menuBackgroundTex = bmpHandler->loadBitmap("menuBackground", "menu_background.jpg");
    if (menuBackgroundTex == 0) {
        std::cerr << "Nie udalo sie zaladowac tekstury tla menu: menu_background.jpg" << std::endl;
    }
    else {
        std::cout << "Zaladowano teksture tla menu ID: " << menuBackgroundTex << std::endl;
    }

    GLuint nieboBgTexID = bmpHandler->loadBitmap("nieboBackground", "t³o.jpg"); 
    if (nieboBgTexID == 0) {
        std::cerr << "Nie udalo sie zaladowac tekstury tla dla Nieba (t³o.jpg)." << std::endl;
    }
    else {
        std::cout << "Zaladowano teksture tla Niebo ID: " << nieboBgTexID << std::endl;
        engine.setMapBackgroundTexture(GameMap::NIEBO, nieboBgTexID);
    }

    GLuint dzunglaBgTexID = bmpHandler->loadBitmap("dzunglaBackground", "d¿ungla.jpg");
    if (dzunglaBgTexID == 0) {
        std::cerr << "Nie udalo sie zaladowac tekstury tla dla Dzungli: d¿ungla.jpg" << std::endl;
    }
    else {
        engine.setMapBackgroundTexture(GameMap::DZUNGLA, dzunglaBgTexID);
    }

    GLuint lodowaBgTexID = bmpHandler->loadBitmap("lodowaBackground", "lodowa.jpg");
    if (lodowaBgTexID == 0) {
        std::cerr << "Nie udalo sie zaladowac tekstury tla dla Lodowej: lodowa.jpg" << std::endl;
    }
    else {
        engine.setMapBackgroundTexture(GameMap::LODOWA, lodowaBgTexID);
    }

    GLuint wulkanBgTexID = bmpHandler->loadBitmap("wulkanBackground", "wulkan.jpg");
    if (wulkanBgTexID == 0) {
        std::cerr << "Nie udalo sie zaladowac tekstury tla dla Wulkanu: wulkan.jpg" << std::endl;
    }
    else {
        engine.setMapBackgroundTexture(GameMap::WULKAN, wulkanBgTexID);
    }

    GLuint pustyniaBgTexID = bmpHandler->loadBitmap("pustyniaBackground", "pustynia.jpg");
    if (pustyniaBgTexID == 0) {
        std::cerr << "Nie udalo sie zaladowac tekstury tla dla Pustyni: pustynia.jpg" << std::endl;
    }
    else {
        engine.setMapBackgroundTexture(GameMap::PUSTYNIA, pustyniaBgTexID);
    }

    MenuScene* menuScene = new MenuScene(&engine);
    engine.addObject(menuScene);
    engine.setMenuScene(menuScene); 


    engine.setupView(
        500.0f,
        0.1f,
        75.0f,
        glm::vec3(0, 5, 10),
        glm::vec3(0, 0, 0)
    );

    engine.setupLight(
        glm::vec3(0.3f, 0.3f, 0.35f),
        glm::vec3(0.9f, 0.9f, 0.85f),
        glm::vec3(0.8f, 0.8f, 0.8f),
        glm::vec3(0.0f, 20.0f, 10.0f),
        true
    );

    std::cout << "Konfiguracja zakonczona. Uruchamianie silnika..." << std::endl;
    engine.run();

    std::cout << "Aplikacja zakonczona." << std::endl;
    return 0;
}