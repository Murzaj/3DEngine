#pragma once


#include <vector>

class Shape3D {
protected:
  std::vector<float> verts;
  std::vector<float> colors;
  std::vector<unsigned char> indices;
public:
  virtual void draw();
};
