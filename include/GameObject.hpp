
#pragma once

#include "Initializer.hpp"

class GameObject {
public:
  virtual bool init(Initializer* initializer) {return true;};
};

