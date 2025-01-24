#pragma once

#include "PrimitiveShape3D.hpp"
#include <GL/glut.h>

class SphereShape3D : public PrimitiveShape3D {
protected:
  unsigned slices;
  unsigned stacks;
  double radius;
  virtual void primitiveDrawingFunc() override {
    glutSolidSphere(radius, slices, stacks);
  }
public:
  SphereShape3D(const glm::vec3 &color, double radius, unsigned slices, unsigned stacks) : 
  PrimitiveShape3D(color),
  radius(radius),
  slices(slices),
  stacks(stacks) {}
};

