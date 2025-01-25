#include "InputMap.hpp"
#include <stdexcept>

bool InputMap::isKeyDown(unsigned char key) const {
  try {
    return pressedKeys.at(key);
  } catch (std::out_of_range e) {
    return false;
  }
}
bool InputMap::isKeyJustPressed(unsigned char key) const {
  try {
    if(pressedKeys.at(key)) {
      try {
        return !prevFrameKeys.at(key);
      }
      catch (std::out_of_range e) {
          return true;
      }
    }
  } catch (std::out_of_range e) {
    return false;
  }
  return false;
}

glm::vec2 InputMap::getMouseMotion() const {
  return mouseMotion;
}

MouseButtons InputMap::getMouseButtons() const {
  return buttons;
}


// setters - for engine to handle
void InputMap::setKeyDown(unsigned char key) {
  pressedKeys[key] = true;
  
}
void InputMap::setKeyUp(unsigned char key){
  pressedKeys[key] = false;
}

void InputMap::setLeftClickDown(){
  buttons.left = true;
}

void InputMap::setLeftClickUp(){
  buttons.left = false;
}

void InputMap::setRightClickDown(){
  buttons.right = true;
}

void InputMap::setRightClickUp(){
  buttons.right = false;
}

void InputMap::setMouseMotion(float x, float y){
  mouseMotion = glm::vec2(x, y);
}

void InputMap::setWheelDirection(int direction) {
  wheelDirection = direction;
}

void InputMap::resetTemporary() {
  wheelDirection = 0;
  mouseMotion = glm::vec2(0.0f);
  prevFrameKeys = pressedKeys;
}

