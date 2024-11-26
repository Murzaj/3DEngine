#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <GL/glut.h>
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Engine");
    return 0;

}