#include "Engine.hpp"
#include "CubeSmooth3D.hpp"
#include "ModelLoader.hpp"

#include <GL/freeglut.h>
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glew.h>
#include <GL/glu.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>

#include "Cube3D.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "ext/stb_image.h"


Engine *Engine::instance = nullptr;

Engine::Engine() {
  name = "3D Engine";
  width = 800;
  height = 600;
  fixedUpdateMs = 20;
  fullscreen = false;
  displayMode = GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH;
  gem = modelloader::shapeFromOBJ("gem.obj");
  orb = modelloader::shapeFromOBJ("orb.obj");
  donut = modelloader::shapeFromOBJ("Donut.obj");
  observer = new Observer(glm::vec3(0,1,4), glm::vec3(0), glm::vec3(0,1,0));
  cube = new CubeSmooth3D();
  cube->translate(glm::vec3(-3,0,0));
  cube->scale(glm::vec3(0.8));
}

Engine::~Engine() { 
  delete gem;
  delete orb;
  delete donut;
  delete observer;
  delete cube;
  instance = nullptr;
}

void Engine::display() {
  const auto view = observer->getTransform();

  glShadeModel(GL_SMOOTH);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity(); // Reset transformations
  // Set up the projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf(glm::value_ptr(projection));
  // Set up the view matrix (camera)
  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixf(glm::value_ptr(view));


  GLfloat amb[] = {0.2, 0.2, 0.2, 1.0}; // RGBA
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);

  GLfloat diff[] = {0.9, 0.9, 0.9, 1.0}; // RGBA
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
  GLfloat spec[] = {1.0, 1.0, 1.0, 1.0}; // RGBA
  //
  glLightfv(GL_LIGHT0, GL_SPECULAR, spec);

  GLfloat pos[] = {4.0, 2.0, 0.0, 1.0};
  glLightfv(GL_LIGHT0, GL_POSITION, pos);

  //glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
  //glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.0);
  glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 1.0);


  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

  /*
  GLfloat amb_diff[] = {0.0, 0.0, 1.0, 1.0};
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amb_diff);
  */
  GLfloat specul[] = {1.0, 1.0, 1.0, 1.0};
  glMaterialfv(GL_FRONT, GL_SPECULAR, specul);
  GLfloat emiss[] = {0.0, 0.0, 0.0, 1.0};
  glMaterialfv(GL_FRONT, GL_EMISSION, emiss);



  // Draw a red solid teapot
  /*
  glm::mat4 teapotTransform =
      glm::translate(view, glm::vec3(-1.0f, 1.0f, 0.0f));
  teapotTransform = glm::rotate(teapotTransform, glm::radians(-angle),
                                glm::vec3(0.0f, 1.0f, 0.0f));
  glColor3f(1.0f, 0.0f, 0.0f);
  glLoadMatrixf(glm::value_ptr(teapotTransform));
  glutSolidTeapot(0.5);
  */


  /*
  glm::mat4 gemT =
      glm::translate(view, glm::vec3(-1.0f, 1.0f, 0.0f));
  gemT = glm::rotate(gemT, glm::radians(-angle),
                                glm::vec3(0.0f, 1.0f, 0.0f));
                              */
  glColor3f(0.8, 1.0, 1.0);
  glm::mat4 cubeMVP = view * cube->getTransform();
  glLoadMatrixf(glm::value_ptr(cubeMVP));
  glutSolidTeapot(1.0f);


  glColor3f(1.0, 0.0, 0.0);
  orb->setTransform(view);
  orb->translate(glm::vec3(sphereX, sphereY, 0.0f));
  glLoadMatrixf(glm::value_ptr(orb->getTransform()));
  orb->draw();



  glm::mat4 ballT(view);
  ballT = glm::translate(ballT, glm::vec3(sphereX, sphereY, 0.0f));
  glLoadMatrixf(glm::value_ptr(ballT));
  glutSolidSphere(1.1f, 24, 12);



  glColor3f(1.0f, 0.0f, 0.0f);
  glm::mat4 donutT(view);
  // translate, then scale, then rotate!
  donutT = glm::translate(donutT, glm::vec3(-1.0f, -1.0f, 0.0f));
  donutT = glm::scale(donutT, glm::vec3(0.5f));
  donutT = glm::rotate(donutT, glm::radians(-angle),
                              glm::vec3(0.0f, 1.0f, 1.0f));
  glLoadMatrixf(glm::value_ptr(donutT));

  glBindTexture(GL_TEXTURE_2D, testRockTexture);
  cube->draw();
  glBindTexture(GL_TEXTURE_2D, 0);

  // originally glutWireCone
  glm::mat4 cubeT(view);
  cubeT = glm::translate(cubeT, glm::vec3(1.0f, -1.0f, 0.0f));
  cubeT =
      glm::rotate(cubeT, glm::radians(angle), glm::vec3(0.0, 1.0, 0.0));
  glColor3f(1.0f, 1.0f, 0.0f);
  glLoadMatrixf(glm::value_ptr(cubeT));
  //glutWireCone(0.5, 1.0, 20, 20);

  glutSwapBuffers();
}

void Engine::fixedUpdate() {
  angle += 1.0f;
  if (angle >= 360.0f) {
    angle -= 360.0f;
  }
  cube->rotate(glm::radians(1.0f), glm::vec3(0,1,0));
}

void Engine::setupTimer() {
  // TODO: this is temporary
  glutTimerFunc(
      fixedUpdateMs,
      [](int x) {
        instance->fixedUpdate();
        instance->setupTimer();
        glutPostRedisplay();
      },
      1);
}


void Engine::onSpecial(int key, int x, int y) {}

void Engine::onSpecialUp(int key, int x, int y) {}

void Engine::onKeyboard(unsigned char key, int x, int y) {
  if (key == 27) {
    std::exit(0);
  }
  if (key == 'a') {
    sphereX += .2f;
  }
  if (key == 'd') {
    sphereX -= .2f;
  }
  if (key == 'w') {
    sphereY += .2f;
  }
  if (key == 's') {
    sphereY -= .2f;
  }
}

void Engine::onKeyboardUp(unsigned char key, int x, int y) {}
void Engine::mainLoop() { glutMainLoop(); }

void Engine::onReshape(int width, int height) {
  this->width = width;
  this->height = height;
  projection =
      glm::perspective(fov, (float)width / (float)height, nearPlane, farPlane);
  glViewport(0, 0, width, height);
}

void Engine::setFixedUpdateFps(float fps) { fixedUpdateMs = 1000 / fps; }

void Engine::setVideoMode(int width, int height, bool fullscreen,
                          bool zBuffer) {
  this->width = width;
  this->height = height;
  this->fullscreen = fullscreen;
  displayMode = GLUT_RGB | GLUT_DOUBLE;
  if (zBuffer) {
    displayMode |= GLUT_DEPTH;
  }
}

void Engine::setClearColor(const glm::vec4 &clearColor) {
  glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
}

void Engine::onMotion(int x, int y) {
  if (warped) {
    warped = false;
    return;
  }
  int halfw = width / 2;
  int halfh = height / 2;

  if (x != halfw || y != halfh) {
    glutWarpPointer(halfw, halfh);
    warped = true;
  }

  int dx = x - halfw;
  if (std::abs(dx) >= 0) {
    observer->rotate(dx / 100.f, glm::vec3(0.0, 1.0, 0.0));
  }
}

void Engine::onMouseWheel(int wheel, int direction, int x, int y) {
  const float DEG_IN_RAD = 0.01745329;
  fov -= direction * DEG_IN_RAD;
  projection =
      glm::perspective(fov, (float)width / (float)height, nearPlane, farPlane);
}

void Engine::initialize(int *argc, char *argv[]) {
  if (instance != nullptr) {
  }

  instance = this;

  glutInit(argc, argv);
  glutInitContextVersion(3, 3);
  glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
  glutSetOption(GLUT_MULTISAMPLE, 4);
  glutInitDisplayMode(displayMode);
  glutInitWindowSize(width, height);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(name.c_str());
  if (fullscreen) {
    glutFullScreen();
  }
  glutSetCursor(GLUT_CURSOR_NONE);
  glewInit();

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_TEXTURE_2D);
  glClearColor(0.0f, 0.0f, 0.1f, 1.0f);

  // take care of textures
  glGenTextures(1, &testRockTexture);
  glBindTexture(GL_TEXTURE_2D, testRockTexture);
  int width, height, nchan;
  unsigned char* dt;
  dt = stbi_load("texture.jpg", &width, &height, &nchan, 0);
  if (!dt) exit(0);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, dt);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  stbi_image_free(dt);



  const float DEG_IN_RAD = 0.01745329;
  fov = 80 * DEG_IN_RAD;

  nearPlane = 0.1f;
  farPlane = 100.0f;
  projection = glm::perspective(fov, width / (float)height, nearPlane, farPlane);


  // temporary
  instance->setupTimer();

  glutIgnoreKeyRepeat(true);
  glutDisplayFunc([]() { instance->display(); });
  glutSpecialFunc(
      [](int key, int x, int y) { instance->onSpecial(key, x, y); });
  glutSpecialUpFunc(
      [](int key, int x, int y) { instance->onSpecialUp(key, x, y); });
  glutKeyboardFunc(
      [](unsigned char key, int x, int y) { instance->onKeyboard(key, x, y); });
  glutKeyboardUpFunc([](unsigned char key, int x, int y) {
    instance->onKeyboardUp(key, x, y);
  });
  glutReshapeFunc([](int w, int h) { instance->onReshape(w, h); });
  glutPassiveMotionFunc([](int x, int y) { instance->onMotion(x, y); });
  glutMotionFunc([](int x, int y) { instance->onMotion(x, y); });
  glutMouseWheelFunc([](int wheel, int direction, int x, int y) {
    instance->onMouseWheel(wheel, direction, x, y);
  });

  mainLoop();
}
