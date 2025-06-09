#define GLM_ENABLE_EXPERIMENTAL
#include "game/GameScene.hpp"
#include "game/Spike.hpp"
#include "EngineManager.hpp"
#include "Engine.hpp"
#include "Initializer.hpp"
#include "BitmapHandler.hpp"
#include "TransformableObject.hpp"
#include "PrimitiveShape3D.hpp"
#include "game/ColoredPlane3D.hpp"
#include "TexturedPlane3D.hpp"
#include "CubeShape3D.hpp"
#include <GL/glew.h>
#include <iostream> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <algorithm>
#include <vector>
#include <random>
#include <stdexcept>
#include <cmath>

GameScene::GameScene()
    : playerController(nullptr, 0.5f),
    spikeTexture(0),
    platformTexture(0),
    forwardSpeed(5.0f),
    speedIncrease(0.3f),
    nextSpikeZ(-30.0f),
    rng(std::random_device{}()),
    leftWall(nullptr),
    rightWall(nullptr),
    score(0.0f),
    playerDead(false)
{
}

GameScene::GameScene(Shape3D* playerShape, float playerRadius, GLuint spikeTex)
    : playerController(playerShape, playerRadius),
    spikeTexture(spikeTex),
    platformTexture(0),
    forwardSpeed(5.0f),
    speedIncrease(0.3f),
    nextSpikeZ(-30.0f),
    rng(std::random_device{}()),
    leftWall(nullptr),
    rightWall(nullptr),
    score(0.0f),
    playerDead(false)
{
    playerController.platformSurfaceY = platformY;
    float startY = platformY + playerRadius + 0.1f;
    playerController.setPosition(glm::vec3(0.0f, startY, 0.0f));
}

GameScene::~GameScene() {
    std::cout << "GameScene Destruktor: Rozpoczynanie usuwania obiektów gry..." << std::endl;
    if (engineManager) {
        for (Spike* spike : spikes) {
            if (spike) {
                engineManager->removeObject(spike);
            }
        }
        spikes.clear(); 

        if (platform) {
            engineManager->removeObject(platform);
            platform = nullptr;
        }
        if (leftWall) {
            engineManager->removeObject(leftWall);
            leftWall = nullptr;
        }
        if (rightWall) {
            engineManager->removeObject(rightWall);
            rightWall = nullptr;
        }

        if (playerController.getShape()) {
            engineManager->removeObject(playerController.getShape());
        }
        std::cout << "GameScene Destruktor: Zakoñczono zg³aszanie obiektów do usuniêcia przez silnik." << std::endl;
        Shape3D* currentShape = playerController.getShape(); 
        if (currentShape) {
            std::cout << "  GameScene Destruktor (" << this << "): Zg³aszanie kszta³tu gracza (" << currentShape << ") do usuniêcia." << std::endl;
            engineManager->removeObject(currentShape);
        }
        else {
            std::cout << "  GameScene Destruktor (" << this << "): Kszta³t gracza jest nullptr, nic do usuniêcia." << std::endl;
        }
    
    }
    else {
        std::cerr << "GameScene Destruktor: engineManager jest nullptr! Nie mo¿na zg³osiæ obiektów gry do usuniêcia." << std::endl;
    }
}

void GameScene::resetGame() {
    playerDead = false;
    score = 0.0f;
    forwardSpeed = 5.0f;
    nextSpikeZ = -30.0f;

    float playerRadius = playerController.getRadius();
    float startY = platformY + playerRadius + 0.1f;
    playerController.setPosition(glm::vec3(0.0f, startY, 0.0f));

    if (engineManager) {
        for (Spike* spike : spikes) {
            if (spike) {
                engineManager->removeObject(spike);
            }
        }
    }
    spikes.clear();

    Initializer* initializer = dynamic_cast<Initializer*>(engineManager);
    if (initializer) {
        for (int i = 0; i < 15; ++i) {
            spawnSpike(initializer);
        }
    }

    if (auto transformablePlatform = dynamic_cast<TransformableObject*>(platform)) {
        glm::vec3 platformInitialTranslation = glm::vec3(0.0f, platformY, -platformLength / 2.0f + 5.0f);
        glm::mat4 currentTransform = transformablePlatform->getTransform();
        glm::vec3 currentScale;
        glm::quat currentRotation;
        glm::vec3 currentTranslation;
        glm::vec3 currentSkew;
        glm::vec4 currentPerspective;
        glm::decompose(currentTransform, currentScale, currentRotation, currentTranslation, currentSkew, currentPerspective);

        glm::mat4 newTransform = glm::mat4(1.0f);
        newTransform = glm::translate(newTransform, platformInitialTranslation);
        newTransform = newTransform * glm::mat4_cast(currentRotation);
        newTransform = glm::scale(newTransform, currentScale);
        transformablePlatform->setTransform(newTransform);

        if (leftWall) {
            if (auto transformableLW = dynamic_cast<TransformableObject*>(leftWall)) {
                float leftWallX = -platformWidth / 2.0f - wallThickness / 2.0f;
                float wallCenterY = platformY + wallHeight / 2.0f;
                glm::mat4 lwTransform = glm::mat4(1.0f);
                lwTransform = glm::translate(lwTransform, glm::vec3(leftWallX, wallCenterY, platformInitialTranslation.z));
                glm::vec3 lwScale; glm::quat lwRot; glm::vec3 lwTrans, lwSkew; glm::vec4 lwPersp;
                glm::decompose(transformableLW->getTransform(), lwScale, lwRot, lwTrans, lwSkew, lwPersp);
                lwTransform = lwTransform * glm::mat4_cast(lwRot) * glm::scale(glm::mat4(1.0f), lwScale);
                transformableLW->setTransform(lwTransform);
            }
        }
        if (rightWall) {
            if (auto transformableRW = dynamic_cast<TransformableObject*>(rightWall)) {
                float rightWallX = platformWidth / 2.0f + wallThickness / 2.0f;
                float wallCenterY = platformY + wallHeight / 2.0f;
                glm::mat4 rwTransform = glm::mat4(1.0f);
                rwTransform = glm::translate(rwTransform, glm::vec3(rightWallX, wallCenterY, platformInitialTranslation.z));
                glm::vec3 rwScale; glm::quat rwRot; glm::vec3 rwTrans, rwSkew; glm::vec4 rwPersp;
                glm::decompose(transformableRW->getTransform(), rwScale, rwRot, rwTrans, rwSkew, rwPersp);
                rwTransform = rwTransform * glm::mat4_cast(rwRot) * glm::scale(glm::mat4(1.0f), rwScale);
                transformableRW->setTransform(rwTransform);
            }
        }
    }
}

void GameScene::initializeDistributionsIfNeeded() {
    if (!distributionX_initialized) {
        float playerRadius = playerController.getRadius();
        float dist_x_min = -platformWidth / 2.0f + playerRadius + 0.5f;
        float dist_x_max = platformWidth / 2.0f - playerRadius - 0.5f;
        if (dist_x_min >= dist_x_max) {
            dist_x_min = -platformWidth / 4.0f;
            dist_x_max = platformWidth / 4.0f;
        }
        distributionX = std::uniform_real_distribution<float>(dist_x_min, dist_x_max);
        distributionX_initialized = true;
    }
    if (!distributionZOffset_initialized) {
        float dist_z_min = 3.0f + playerController.getRadius() * 2.0f;
        float dist_z_max = 8.0f + playerController.getRadius() * 2.0f;
        if (dist_z_min >= dist_z_max) {
            dist_z_min = 4.0f;
            dist_z_max = 7.0f;
        }
        distributionZOffset = std::uniform_real_distribution<float>(dist_z_min, dist_z_max);
        distributionZOffset_initialized = true;
    }
}

bool GameScene::init(Initializer* initializer) {
    engineManager = initializer->getEngineManager();
    if (!engineManager) { return false; }
    BitmapHandler* bmpHandler = initializer->getBitmapHandler();
    if (!bmpHandler) { return false; }

    if (!playerController.init(initializer)) {
        return false;
    }
    playerController.minX = -platformWidth / 2.0f + playerController.getRadius();
    playerController.maxX = platformWidth / 2.0f - playerController.getRadius();
    playerController.platformSurfaceY = platformY;

    glm::vec3 platformColor(0.3f, 0.6f, 0.3f);
    platform = new ColoredPlane3D(platformColor);

    glm::vec3 platformInitialTranslation = glm::vec3(0.0f, platformY, -platformLength / 2.0f + 5.0f);
    if (auto transformablePlatform = dynamic_cast<TransformableObject*>(platform)) {
        transformablePlatform->resetIdentity();
        transformablePlatform->scale(glm::vec3(platformWidth / 2.0f, 1.0f, platformLength / 2.0f));
        transformablePlatform->translate(platformInitialTranslation);
        engineManager->addObject(platform);
    }
    else {
        delete platform; platform = nullptr; return false;
    }

    glm::vec3 wallColor = glm::vec3(0.6f, 0.6f, 0.6f);

    leftWall = new CubeShape3D(wallColor, 1.0f);
    if (auto transformableLW = dynamic_cast<TransformableObject*>(leftWall)) {
        transformableLW->resetIdentity();
        transformableLW->scale(glm::vec3(wallThickness, wallHeight, platformLength));
        float leftWallX = -platformWidth / 2.0f - wallThickness / 2.0f;
        float wallCenterY = platformY + wallHeight / 2.0f;
        transformableLW->translate(glm::vec3(leftWallX, wallCenterY, platformInitialTranslation.z));
        engineManager->addObject(leftWall);
    }
    else {
        delete leftWall; leftWall = nullptr;
    }

    rightWall = new CubeShape3D(wallColor, 1.0f);
    if (auto transformableRW = dynamic_cast<TransformableObject*>(rightWall)) {
        transformableRW->resetIdentity();
        transformableRW->scale(glm::vec3(wallThickness, wallHeight, platformLength));
        float rightWallX = platformWidth / 2.0f + wallThickness / 2.0f;
        float wallCenterY = platformY + wallHeight / 2.0f;
        transformableRW->translate(glm::vec3(rightWallX, wallCenterY, platformInitialTranslation.z));
        engineManager->addObject(rightWall);
    }
    else {
        delete rightWall; rightWall = nullptr;
    }

    resetGame();
    return true;
}

void GameScene::update(float deltaMs, const InputMap& input, EngineManager* eManager) {
    if (playerDead) return;

    float dt = deltaMs / 1000.0f;
    playerController.update(deltaMs, input, eManager);
    playerController.moveForward(forwardSpeed * dt);
    forwardSpeed += speedIncrease * dt;
    score += forwardSpeed * dt;

    Engine* engine = dynamic_cast<Engine*>(eManager);
    if (engine) {
        glm::vec3 playerPosCam = playerController.getPosition();
        glm::vec3 cameraPos = playerPosCam + glm::vec3(0.0f, 3.0f, 8.0f);
        glm::vec3 lookAtPos = playerPosCam + glm::vec3(0.0f, 0.0f, -2.0f);
        if (engine->getObserver()) {
            engine->getObserver()->lookAt(cameraPos, lookAtPos);
        }
    }

    cleanupSpikes();
    manageSpawns(dynamic_cast<Initializer*>(eManager));
    checkCollisions(eManager);

    if (engine) {
        glm::vec3 playerPosFall = playerController.getPosition();
        float fallThreshold = platformY - playerController.getRadius() * 5.0f;
        if (playerPosFall.y < fallThreshold && !playerDead) {
            playerDead = true;
            engine->gameOver(static_cast<int>(score));
        }
    }

    glm::vec3 playerPosScroll = playerController.getPosition();
    if (auto transformablePlatform = dynamic_cast<TransformableObject*>(platform)) {
        glm::vec3 platformCurrentPos = transformablePlatform->getPositionFromTransform();
        if (playerPosScroll.z < platformCurrentPos.z - (platformLength / 4.0f)) {
            float newPlatformZ = platformCurrentPos.z - platformLength;
            transformablePlatform->setPositionInTransform(glm::vec3(platformCurrentPos.x, platformCurrentPos.y, newPlatformZ));

            if (leftWall) {
                if (auto transformableLW = dynamic_cast<TransformableObject*>(leftWall)) {
                    glm::vec3 lwPos = transformableLW->getPositionFromTransform();
                    transformableLW->setPositionInTransform(glm::vec3(lwPos.x, lwPos.y, newPlatformZ));
                }
            }
            if (rightWall) {
                if (auto transformableRW = dynamic_cast<TransformableObject*>(rightWall)) {
                    glm::vec3 rwPos = transformableRW->getPositionFromTransform();
                    transformableRW->setPositionInTransform(glm::vec3(rwPos.x, rwPos.y, newPlatformZ));
                }
            }
        }
    }
}

void GameScene::spawnSpike(Initializer* initializer) {
    initializeDistributionsIfNeeded();

    if (!initializer) {
        return;
    }
    EngineManager* mgr = initializer->getEngineManager();
    if (!mgr) {
        return;
    }

    auto* spike = new Spike(spikeTexture);
    if (!spike) {
        return;
    }

    float x_pos_rand = distributionX(rng);
    float z_pos_depth = nextSpikeZ;
    float y_pos_on_platform = platformY;

    spike->resetIdentity();
    spike->rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    spike->setPositionInTransform(glm::vec3(x_pos_rand, y_pos_on_platform, z_pos_depth));

    mgr->addObject(spike);
    spikes.push_back(spike);

    nextSpikeZ -= distributionZOffset(rng);
}

void GameScene::checkCollisions(EngineManager* eManager) {
    if (playerDead) return;

    Engine* engine = dynamic_cast<Engine*>(eManager);
    if (!engine) return;

    glm::vec3 playerPos = playerController.getPosition();
    float playerRadius = playerController.getRadius();

    for (const auto* spike : spikes) {
        if (!spike) continue;
        glm::vec3 spikeBasePos = spike->getPositionFromTransform();

        float spikeEffectRadius = spike->getRadius() * 0.8f;
        float spikeHeight = spike->getHeight();
        float spikePosY = platformY;
        float spikeTipY = platformY + spikeHeight;

        bool y_overlap = (playerPos.y - playerRadius < spikeTipY) && (playerPos.y + playerRadius > spikePosY);

        if (y_overlap) {
            float dx = playerPos.x - spikeBasePos.x;
            float dz = playerPos.z - spikeBasePos.z;
            float distSqXZ = dx * dx + dz * dz;
            float radiiSum = playerRadius + spikeEffectRadius;
            float radiiSumSq = radiiSum * radiiSum;

            if (distSqXZ < radiiSumSq) {
                playerDead = true;
                engine->gameOver(static_cast<int>(score));
                return;
            }
        }
    }
}

void GameScene::cleanupSpikes() {
    if (!engineManager || playerDead) return;

    float playerZ = playerController.getPosition().z;
    float cleanupDistanceBehind = 20.0f;

    spikes.erase(std::remove_if(spikes.begin(), spikes.end(),
        [&](Spike* spike) {
            if (!spike) return true;
            glm::vec3 spikePos = spike->getPositionFromTransform();
            bool shouldRemove = spikePos.z > playerZ + cleanupDistanceBehind;
            if (shouldRemove) {
                engineManager->removeObject(spike);
            }
            return shouldRemove;
        }), spikes.end());
}

void GameScene::manageSpawns(Initializer* initializer) {
    if (!initializer || playerDead) return;

    float playerZ = playerController.getPosition().z;
    float spawnLookAhead = 70.0f;

    while (nextSpikeZ > playerZ - spawnLookAhead) {
        spawnSpike(initializer);
    }
}

int GameScene::getScore() const {
    return static_cast<int>(score);
}