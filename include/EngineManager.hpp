#pragma once

#include "GameObject.hpp"
#include <typeinfo>

class EngineManager {
public:
  virtual void addObject(GameObject *obj) = 0;
  virtual void removeObject(GameObject *obj) = 0;
  virtual GameObject *getFirstOfType(const std::type_info &type) const = 0;
  virtual void stop() = 0;
};
