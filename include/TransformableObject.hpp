#pragma once

#include <glm/ext/matrix_float4x4.hpp>

class TransformableObject {
protected:
  glm::mat4 transform;
public:
  TransformableObject(const glm::mat4& transform);
  TransformableObject();
  void resetIdentity();
  void translate(const glm::vec3 &vec);
  void rotate(float angle, const glm::vec3 &axis);
  void scale(const glm::vec3 &scale);
  glm::mat4 getTransform() const;
  void setTransform(const glm::mat4& newTransform);
};
