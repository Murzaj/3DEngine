#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GL/glut.h>
#include "Engine.hpp"

int main(int argc, char **argv) 
{   
    Engine engine;
    engine.setVideoMode(800, 600, true, true);
    engine.initialize(&argc, argv);
    return 0;
}
