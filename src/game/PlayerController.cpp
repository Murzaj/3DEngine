#include "game/PlayerController.hpp"
#include "EngineManager.hpp"
#include "Shape3D.hpp"
#include "TransformableObject.hpp"
#include <iostream>
#include <algorithm> 

const float GRAVITY = 9.81f * 2.0f;


PlayerController::PlayerController(Shape3D* playerShape, float playerRadius)
    : shape(playerShape),
    radius(playerRadius),
    position(0.0f, 0.0f, 0.0f),
    engineManager(nullptr),
    velocityY(0.0f),
    platformSurfaceY(-1.0f)
{
    if (!shape) {
        std::cerr << "Ksztalt jest null w konstruktorze!" << std::endl;
    }
}


bool PlayerController::init(Initializer* initializer)
{
    if (!initializer) { return false; }
    engineManager = initializer->getEngineManager();
    if (!engineManager) { return false; }



    if (auto transformableShape = dynamic_cast<TransformableObject*>(shape)) {
        engineManager->addObject(shape);
        transformableShape->resetIdentity();
        transformableShape->translate(position);
        std::cout << "PlayerController::init: Dodano ksztalt gracza do silnika i ustawiono pozycje." << std::endl; 
    }
    else {
        std::cerr << "Ksztalt nie jest TransformableObject" << std::endl;
        if (shape) {
            engineManager->addObject(shape);
            std::cerr << "Dodano ksztalt jako GameObject, ale transformacja moze nie dzialac poprawnie." << std::endl;
        }
        else {
            return false;
        }
    }
    return true;
}


void PlayerController::update(float deltaMs, const InputMap& input, EngineManager* manager)
{
    float dt = deltaMs / 1000.0f;

 
    float dx = 0.0f;
    if (input.isKeyDown('a') || input.isKeyDown('A')) {
        dx -= sideSpeed * dt;
    }
    if (input.isKeyDown('d') || input.isKeyDown('D')) {
        dx += sideSpeed * dt;
    }
    position.x += dx;


    position.x = std::clamp(position.x, minX, maxX);


    velocityY -= GRAVITY * dt;
    position.y += velocityY * dt;


    float floorLevel = platformSurfaceY + radius;
    if (position.y < floorLevel) {
        position.y = floorLevel;
        velocityY = 0.0f;
    }


    if (auto transformableShape = dynamic_cast<TransformableObject*>(shape)) {
        transformableShape->resetIdentity();
        transformableShape->translate(position);
    }
}
void PlayerController::moveForward(float distance)
{
    position.z -= distance;
}


void PlayerController::setPosition(const glm::vec3& pos) {
    position = pos;
    position.x = std::clamp(position.x, minX, maxX);
    position.y = std::max(position.y, platformSurfaceY + radius);
    velocityY = 0.0f;

    if (auto transformableShape = dynamic_cast<TransformableObject*>(shape)) {
        transformableShape->resetIdentity();
        transformableShape->translate(position);
    }
}

float PlayerController::getZ() const { return position.z; }
glm::vec3 PlayerController::getPosition() const { return position; }
float PlayerController::getRadius() const { return radius; }

Shape3D* PlayerController::getShape() const {
    return shape;
}