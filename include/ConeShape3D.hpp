
#pragma once

#include "PrimitiveShape3D.hpp"
#include <GL/glut.h>

class ConeShape3D : public PrimitiveShape3D {
protected:
  unsigned slices;
  unsigned stacks;
  double height;
  double base;
  virtual void primitiveDrawingFunc() override {
    glutSolidCone(base, height, slices, stacks);
  }
public:
  ConeShape3D(const glm::vec3 &color, double base, double height, unsigned slices, unsigned stacks) : 
  PrimitiveShape3D(color),
  base(base),
  height(height),
  slices(slices),
  stacks(stacks) {}
};

