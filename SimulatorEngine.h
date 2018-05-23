#ifndef CPPTEST_SIMULATORENGINE_H
#define CPPTEST_SIMULATORENGINE_H


#include "Model.h"

using namespace std;

class SimulatorEngine {
public:
    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);

private:
    int width;
    int height;
    void initializeOpenGL();
public:

    static GLFWwindow *window;
    static float aspectRatio;
    SimulatorEngine();
    bool initialize();
    bool initialize(int windowWidth, int windowHeight, const string &windowTitle);
    void finalize();

};

#endif //CPPTEST_SIMULATORENGINE_H
