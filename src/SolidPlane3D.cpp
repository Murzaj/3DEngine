#include "SolidPlane3D.hpp"
#include <GL/glew.h>

SolidPlane3D::SolidPlane3D(float halfSize, const glm::vec3& color)
    : PrimitiveShape3D(glm::vec4(color, 1.0f)), halfSize(halfSize), color(color)
{
}

void SolidPlane3D::primitiveDrawingFunc() {
    float s = halfSize;
    glColor3fv(&color.x);
    glBegin(GL_QUADS);
    glVertex3f(-s, 0.0f, s);
    glVertex3f(s, 0.0f, s);
    glVertex3f(s, 0.0f, -s);
    glVertex3f(-s, 0.0f, -s);
    glEnd();
}