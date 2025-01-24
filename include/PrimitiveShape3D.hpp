#pragma once 

#include "Shape3D.hpp"
#include <glm/glm.hpp>

class PrimitiveShape3D : public Shape3D {
protected: 
  glm::vec3 color;
  virtual void primitiveDrawingFunc() = 0;
public:
  PrimitiveShape3D(const glm::vec3 &color) : color(color) {}
  virtual void draw(const glm::mat4 &view) override;
};
