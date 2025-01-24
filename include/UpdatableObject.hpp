#pragma once

#include "Engine.hpp"
#include "GameObject.hpp"
#include "ObjectManager.hpp"

class UpdatableObject : public virtual GameObject {
public:
  virtual void update(float delta, const InputMap &input, ObjectManager* manager) = 0;
};
