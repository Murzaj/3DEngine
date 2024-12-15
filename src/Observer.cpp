#include "Observer.hpp"
#include <glm/ext/matrix_transform.hpp>


Observer::Observer(const glm::vec3 &pos, const glm::vec3 &target, const glm::vec3 &up)
: TransformableObject(glm::lookAt(pos, target, up))
{}

void Observer::lookAt(const glm::vec3 &pos, const glm::vec3 &target, const glm::vec3 &up) {
  setTransform(glm::lookAt(pos, target, up));
}
