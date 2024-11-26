#include "Engine.hpp"
#include <GL/glew.h>
#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#include <glm/glm.hpp>

Engine *Engine::instance = nullptr;



Engine::Engine() {
    name = "3D Engine";
}

void Engine::display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);

 
    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);
    
    glutSwapBuffers();
}

void Engine::onKeyboard(unsigned char key, int x, int y) {
    if (key == 27) {
        std::exit(0);
    }

    std::cout << "Pressed: " << key << ", pos: " << x << ", " << y << "\n";
}

Engine::~Engine() {
    instance = nullptr;
}


void Engine::mainLoop() {
    glutMainLoop();
}


void Engine::initialize(int* argc, char* argv[]) {
    if (instance != nullptr) {
        throw std::exception("Already initialized.");
    }


    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow(name.c_str());

    // setup triangle buffer
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // An array of 3 vectors which represents 3 vertices
    static const GLfloat triangle_buffer_data[] = {
       -1.0f, -1.0f, 0.0f,
       1.0f, -1.0f, 0.0f,
       0.0f,  1.0f, 0.0f,
    };

    glGenBuffers(1, &vertexbuffer); // generate one buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_buffer_data), triangle_buffer_data, GL_STATIC_DRAW);
    // end setup triangle buffer


    glutDisplayFunc([]() {instance->display(); });
    glutKeyboardFunc([](unsigned char key, int x, int y) {instance->onKeyboard(key, x, y); });

    mainLoop();

}
