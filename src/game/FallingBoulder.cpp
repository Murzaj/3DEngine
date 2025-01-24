#include "game/FallingBoulder.hpp"
#include <iostream>
#include <ostream>
#include <random>

FallingBoulder::FallingBoulder(glm::vec3 origin, glm::vec3 spread, float speedMin, float speedMax, float sizeMin, float sizeMax, float deathY, Shape3D *boulderModel) :

boulderModel(boulderModel), deathY(deathY), spread(spread),
xDistribution(origin.x-spread.x, origin.x+spread.x),
yDistribution(origin.y-spread.y, origin.y+spread.y),
zDistribution(origin.z-spread.z, origin.z+spread.z),
speedDistribution(speedMin, speedMax),
sizeDistribution(sizeMin, sizeMax)
{
  place();
}


void FallingBoulder::place() {
  resetIdentity();
  y = yDistribution(rng);
  speed = speedDistribution(rng);
  std::cout << "SPEED: " << speed << std::endl;
  translate(glm::vec3(xDistribution(rng), y, zDistribution(rng)));

  size = sizeDistribution(rng);
  scale(glm::vec3(size));
}


void FallingBoulder::update(float delta, const InputMap &input, ObjectManager* manager) {
  float dy = -1.0f*speed*delta/1000;
  y+=dy;
  translate(glm::vec3(0.0, dy, 0.0f));
  if (y <= deathY) {
    place();
    return;
  }
}

void FallingBoulder::draw(const glm::mat4& view) {
  glm::mat4 transform = view * getTransform();
  boulderModel->draw(transform);
}
