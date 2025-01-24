#pragma once

#include "Shape3D.hpp"
#include <vector>

class ModelShape3D : public Shape3D {
protected:
  std::vector<float> verts;
  std::vector<float> colors;
  glm::vec3 modulateColor;
  std::vector<float> normals;
  std::vector<unsigned int> indices;
  std::vector<float> texCoords;
public:
  ModelShape3D(
    const std::vector<float> &verts,
    const std::vector<float> &colors,
    glm::vec3 modulateColor,
    const std::vector<float> &normals,
    const std::vector<unsigned int> &indices,
    const std::vector<float> &texCoord
  );
  virtual void draw(const glm::mat4& view) override;
};
