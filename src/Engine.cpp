#include "Engine.hpp"
#include <GL/glew.h>
#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#include <glm/glm.hpp>
#include <util/Shader.hpp>

Engine *Engine::instance = nullptr;



Engine::Engine() {
    name = "3D Engine";
}

void Engine::display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();


    // Draw a teapot
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    glutSolidTeapot(1.0);

    // Draw a sphere
    glPushMatrix();
    glTranslatef(-2.0f, 0.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f); // Green color
    glutSolidSphere(0.75, 50, 50);
    glPopMatrix();

    // Draw a cube
    glPushMatrix();
    glTranslatef(2.0f, 0.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color
    glutSolidCube(1.5);
    glPopMatrix();

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
    }
    instance = this;

    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow(name.c_str());
    glewInit();

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

    simpleShaderID = util::loadShaders("shader/SimpleVertexShader.vert", "shader/SimpleFragmentShader.frag");

    // bind events to instance using lambdas
    glutDisplayFunc([]() {instance->display(); });
    glutKeyboardFunc([](unsigned char key, int x, int y) {instance->onKeyboard(key, x, y); });

    mainLoop();

}
