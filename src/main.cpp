#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <GL/glut.h>
#include <filesystem>
#include "Engine.hpp"

int main(int argc, char **argv) 
{   

    std::cout << "PWD is: " << std::filesystem::current_path() << '\n';
    Engine engine;
    engine.setVideoMode(1080, 1080, false, true);
    engine.initialize(&argc, argv);
    return 0;
}
