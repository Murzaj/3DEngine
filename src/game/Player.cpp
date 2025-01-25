#include "game/Player.hpp"
#include <glm/common.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/geometric.hpp>
#include <iostream>


Player::Player(Shape3D *playerModel, double size, glm::vec3 startpos)
:size(size), playerModel(playerModel), pos(startpos) {
  playerModel->scale(glm::vec3(size));
}


void Player::draw(const glm::mat4 &view) {
  auto positioned = glm::translate(view, pos);
  playerModel->draw(positioned);
}

void Player::update(float delta, const InputMap &input, EngineManager *manager) {
  if(dead) {
    manager->stop();
    return;
  }
  auto motion = input.getMouseMotion();
  pos.x += motion.x * delta / 200.0f;
  pos.z += motion.y * delta / 200.0f;
  std::cout << "Pos: " << pos.x << ", " << pos.y << ", " << pos.z << std::endl;
  pos = glm::clamp(pos, glm::vec3(-5.0f), glm::vec3(5.0f));
  
}


double Player::getSize() const {
  return size;
}
glm::vec3 Player::getPos() const {
  return pos;
}

void Player::hit() {
  std::cout << "Hit!" << std::endl;
  dead = true;

}
