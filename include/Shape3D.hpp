#pragma once


#include <vector>

class Shape3D {
protected:
  std::vector<float> verts;
  std::vector<float> colors;
  std::vector<unsigned int> indices;
public:
  Shape3D(
    const std::vector<float> &verts,
    const std::vector<float> &colors,
    const std::vector<unsigned int> &indices
  );
  virtual void draw();
};
