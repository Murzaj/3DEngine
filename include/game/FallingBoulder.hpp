#pragma once
#include "UpdatableObject.hpp"
#include "Shape3D.hpp"
#include <random>

class FallingBoulder : public UpdatableObject, public Shape3D {
protected:
  float speed;
  float y;
  glm::vec3 origin;
  glm::vec3 spread;
  float size;
  float deathY;
  Shape3D *boulderModel;

  std::uniform_real_distribution<float> xDistribution;
  std::uniform_real_distribution<float> yDistribution;
  std::uniform_real_distribution<float> zDistribution;
  std::uniform_real_distribution<float> speedDistribution;
  std::uniform_real_distribution<float> sizeDistribution;
  std::mt19937 rng;
public:
  FallingBoulder(glm::vec3 origin, glm::vec3 spread, float speedMin,float speedMax, float sizeMin, float sizeMax, float deathY, Shape3D *boulderModel);
  virtual void update(float delta, const InputMap &input, ObjectManager* manager) override;
  virtual void draw(const glm::mat4& view) override;
  void place();
};
