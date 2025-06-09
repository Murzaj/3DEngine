#include "PrimitiveShape3D.hpp"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include <iostream> 
#define GLM_ENABLE_EXPERIMENTAL 
#include <glm/gtx/string_cast.hpp> 
#include "game/Spike.hpp" 


void PrimitiveShape3D::draw(const glm::mat4& view) {

   
    glm::mat4 currentObjectTransform = getTransform(); 

    glm::mat4 modelView = view * currentObjectTransform;
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(modelView));

    glColor3fv(glm::value_ptr(color));

    if (texture > 0) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
    }
    else {
        glDisable(GL_TEXTURE_2D);
    }

    primitiveDrawingFunc();

    if (texture > 0) {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}