#include "game/Spike.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/constants.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <iostream>



const float Spike::baseRadius = 0.4f;
const float Spike::height = 1.0f;


Spike::Spike(GLuint texture) :
    ConeShape3D(
        glm::vec3(0.8f, 0.1f, 0.1f),
        Spike::baseRadius,
        Spike::height,    
        20,
        20
    )
{

    setTexture(texture);
}