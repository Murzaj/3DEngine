#pragma once

#include "PrimitiveShape3D.hpp"
#include <GL/freeglut_std.h>
#include <GL/glut.h>

class TorusShape3D : public PrimitiveShape3D {
protected:
  double innerRadius;
  double outerRadius;
  GLint sides;
  GLint rings;
  virtual void primitiveDrawingFunc() override {
    glutSolidTorus(innerRadius, outerRadius, sides, rings);
  }
public:
  TorusShape3D(const glm::vec3 &color,
  double innerRadius,
  double outerRadius,
  GLint sides,
  GLint rings) :
  PrimitiveShape3D(color),
  innerRadius(innerRadius),
  outerRadius(outerRadius),
  sides(sides),
  rings(rings) {}
};

