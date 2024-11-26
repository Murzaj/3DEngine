#pragma once

#include <GL/glew.h>
#include <memory>
#include <string>


class Engine {
protected:
    static Engine *instance;
    std::string name;
 

    GLuint vertexbuffer;

public:
    virtual ~Engine();
    void initialize(int* argc, char *argv[]);
    Engine();


    void setDisplayOptions();


    void display();
    void onKeyboard(unsigned char key, int x, int y);
    
    void mainLoop();
};