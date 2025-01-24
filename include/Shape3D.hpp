#pragma once

#include "TransformableObject.hpp"

class Shape3D : public virtual TransformableObject {
public:
  virtual void draw(const glm::mat4 &view) = 0;
  virtual ~Shape3D() {}
};
