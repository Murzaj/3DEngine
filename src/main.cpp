#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <GL/glut.h>
#include "Engine.hpp"
#include <cstdlib>

int main(int argc, char **argv) 
{
    std::cout << "PWD is: " << std::getenv("PWD") << '\n';
    Engine engine;
    engine.initialize(&argc, argv);
    return 0;
}