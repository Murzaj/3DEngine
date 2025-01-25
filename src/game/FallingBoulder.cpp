#include "game/FallingBoulder.hpp"
#include <glm/geometric.hpp>
#include <random>

FallingBoulder::FallingBoulder(glm::vec3 origin, glm::vec3 spread, float speedMin, float speedMax, float sizeMin, float sizeMax, float deathY, Shape3D *boulderModel, std::random_device &rd) :
rng(rd()),
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
  speed = speedDistribution(rng);
  pos = glm::vec3(xDistribution(rng), yDistribution(rng), zDistribution(rng));
  translate(pos);
  size = sizeDistribution(rng);
  scale(glm::vec3(size));
}


void FallingBoulder::update(float delta, const InputMap &input, EngineManager* manager) {
  float dy = -1.0f*speed*delta/1000;
  pos.y+=dy;
  translate(glm::vec3(0.0, dy, 0.0f));
  rotate(dy, glm::vec3(0.0, 1.0, 0.0));

  if (pos.y <= deathY) {
    place();
    return;
  }

  if (player == nullptr) {
    return;
  }

  auto distancePlayer = glm::distance(pos, player->getPos());
  if (distancePlayer < size + player->getSize())
    player->hit();


}

void FallingBoulder::draw(const glm::mat4& view) {
  glm::mat4 transform = view * getTransform();
  boulderModel->draw(transform);
}



bool FallingBoulder::init(Initializer* initializer) {
  auto man = initializer->getEngineManager();
  player = dynamic_cast<Player *>(man->getFirstOfType(typeid(Player)));
  return player != nullptr;
}


