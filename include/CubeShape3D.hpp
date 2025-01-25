#pragma once

#include "PrimitiveShape3D.hpp"
#include <GL/glut.h>

class CubeShape3D : public PrimitiveShape3D {
protected:
  double size;
  virtual void primitiveDrawingFunc() override {
    glutSolidCube(size);
  }
public:
  CubeShape3D(const glm::vec3 &color, double size) : 
  PrimitiveShape3D(color),
  size(size) {}
};

