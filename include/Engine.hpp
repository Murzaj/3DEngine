#pragma once
#include <memory>

class Engine {
protected:
    static Engine *instance;

public:
    const static int FPS = 60;
    const static int WINDOW_WIDTH = 640;
    const static int WINDOW_HEIGHT = 480;
    const static int WINDOW_X_POSITION = 100;
    const static int WINDOW_Y_POSITION = 100;
    const static double FRAME_TIME;
    Engine();
    void initialize(int argc, char *argv[]);
};