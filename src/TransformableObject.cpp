#include "TransformableObject.hpp"
#include <glm/ext/matrix_transform.hpp>

TransformableObject::TransformableObject(const glm::mat4& transform): transform(transform) {}
TransformableObject::TransformableObject(): transform(glm::identity<glm::mat4>()) {}

void TransformableObject::resetIdentity() {
  transform = glm::identity<glm::mat4>();
}

void TransformableObject::translate(const glm::vec3& vec) {
  transform = glm::translate(transform, vec);
}
 
void TransformableObject::rotate(float angle, const glm::vec3 &axis) {
  transform = glm::rotate(transform, angle, axis);
}

void TransformableObject::scale(const glm::vec3& scale) {
  transform = glm::scale(transform, scale);
}

glm::mat4 TransformableObject::getTransform() const {
  return transform;
}

void TransformableObject::setTransform(const glm::mat4& newTransform) {
  transform = newTransform;
}
