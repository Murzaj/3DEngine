#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <GL/glut.h>
#include "Engine.hpp"


int main(int argc, char **argv) {
    Engine engine;
    engine.initialize(&argc, argv);
    return 0;
}