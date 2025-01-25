#pragma once

#include "Engine.hpp"
#include "GameObject.hpp"
#include "EngineManager.hpp"

class UpdatableObject : public virtual GameObject {
public:
  virtual void update(float delta, const InputMap &input, EngineManager* manager) = 0;
};
