#include "TransformableObject.hpp"
#include <glm/gtc/matrix_transform.hpp> 

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp> 
#include <glm/gtx/string_cast.hpp> 
#include <iostream>



TransformableObject::TransformableObject(const glm::mat4& initialTransform)
    : transform(initialTransform) {
}


TransformableObject::TransformableObject()
    : transform(glm::identity<glm::mat4>()) {
}


void TransformableObject::resetIdentity() {
    transform = glm::identity<glm::mat4>();
}


void TransformableObject::translate(const glm::vec3& vec) {
    transform = glm::translate(transform, vec);
}


void TransformableObject::rotate(float angleRadians, const glm::vec3& axis) {
    transform = glm::rotate(transform, angleRadians, axis);
}


void TransformableObject::scale(const glm::vec3& scaleVec) {
    transform = glm::scale(transform, scaleVec);
}


glm::mat4 TransformableObject::getTransform() const {
    return transform;
}


void TransformableObject::setTransform(const glm::mat4& newTransform) {
    transform = newTransform;
}


glm::vec3 TransformableObject::getPositionFromTransform() const {

    return glm::vec3(transform[3]);
}


void TransformableObject::setPositionInTransform(const glm::vec3& pos) {
    transform[3] = glm::vec4(pos, 1.0f);
}