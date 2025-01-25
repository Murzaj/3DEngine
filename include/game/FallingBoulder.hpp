#pragma once
#include "UpdatableObject.hpp"
#include "Shape3D.hpp"
#include "game/Player.hpp"
#include <random>

class FallingBoulder : public UpdatableObject, public Shape3D {
protected:
  float speed;
  glm::vec3 pos;
  glm::vec3 origin;
  glm::vec3 spread;
  float size;
  float deathY;
  Shape3D *boulderModel;
  Player *player;

  std::random_device rd;
  std::uniform_real_distribution<float> xDistribution;
  std::uniform_real_distribution<float> yDistribution;
  std::uniform_real_distribution<float> zDistribution;
  std::uniform_real_distribution<float> speedDistribution;
  std::uniform_real_distribution<float> sizeDistribution;
  std::mt19937 rng;
public:
  FallingBoulder(glm::vec3 origin, glm::vec3 spread, float speedMin,float speedMax, float sizeMin, float sizeMax, float deathY, Shape3D *boulderModel, std::random_device &rd);
  virtual void update(float delta, const InputMap &input, EngineManager* manager) override;
  virtual void draw(const glm::mat4& view) override;
  virtual bool init(Initializer* initializer) override;
  void place();
};
