#include "InputMap.hpp"
#include <iostream>



bool InputMap::isKeyDown(unsigned char key) const {
    return currentKeys.count(key);
}

bool InputMap::isKeyJustPressed(unsigned char key) const {
    return currentKeys.count(key) && !previousKeys.count(key);
}

bool InputMap::isKeyJustReleased(unsigned char key) const {
    return !currentKeys.count(key) && previousKeys.count(key);
}


glm::vec2 InputMap::getMouseDelta() const {
    return mouseDelta;
}

glm::vec2 InputMap::getMousePosition() const {
    return currentMousePos;
}

MouseButtons InputMap::getMouseButtons() const {
    return buttons;
}

int InputMap::getWheelDirection() const {
    return wheelDirection;
}



void InputMap::setKeyDown(unsigned char key) {
    currentKeys.insert(key);
}

void InputMap::setKeyUp(unsigned char key) {
    currentKeys.erase(key);
}

void InputMap::setLeftClickDown() {
    buttons.left = true;
    setKeyDown(MOUSE_LEFT_CLICK_PSEUDO_KEY); 
}
void InputMap::setLeftClickUp() {
    buttons.left = false;
    setKeyUp(MOUSE_LEFT_CLICK_PSEUDO_KEY); 
}
void InputMap::setRightClickDown() { buttons.right = true; }
void InputMap::setRightClickUp() { buttons.right = false; }
void InputMap::setMiddleClickDown() { buttons.middle = true; }
void InputMap::setMiddleClickUp() { buttons.middle = false; }

void InputMap::setMousePosition(int x, int y) {
    currentMousePos = glm::vec2(static_cast<float>(x), static_cast<float>(y));
}

void InputMap::setWheelDirection(int direction) {
    wheelDirection = direction;
}



void InputMap::updateFrameState() {
    previousKeys = currentKeys;



    mouseDelta = currentMousePos - previousMousePos;
    previousMousePos = currentMousePos;


    wheelDirection = 0;
}