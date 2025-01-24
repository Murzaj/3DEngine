#pragma once

#include "ModelShape3D.hpp"

#include <GL/gl.h>
#include <glm/glm.hpp>

class TexturedModelShape3D : public ModelShape3D {
protected:
  GLuint textureId;
public:
  TexturedModelShape3D(const std::vector<float> &verts, const std::vector<float> &colors, glm::vec3 modulateColor, const std::vector<float> &normals, const std::vector<unsigned int> &indices, const std::vector<float> &texCoord, GLuint textureId);
  void draw(const glm::mat4& view) override;
};
