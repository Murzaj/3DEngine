#pragma once

#include "UpdatableObject.hpp"
#include "Shape3D.hpp"

class Player : public UpdatableObject, public Shape3D {
public:
  void draw(const glm::mat4 &view) override;
  void update(float delta, const InputMap &input, EngineManager *manager) override;
  Player(Shape3D *playerModel, double size, glm::vec3 startpos);
  glm::vec3 getPos() const;
  double getSize() const;
  void hit();
protected:
  Shape3D *playerModel;
  bool dead = false;
  double size;
  glm::vec3 pos;
};
