#pragma once 
#include "TransformableObject.hpp"
#include <glm/glm.hpp>

class Observer : public TransformableObject { 
private:
public:
  Observer(const glm::vec3 &pos, const glm::vec3 &target, const glm::vec3 &up);
  void lookAt(const glm::vec3 &pos, const glm::vec3 &target, const glm::vec3 &up);
};
