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
    GLFWwindow * window;
public:
    GLFWwindow *getWindow() const;

    void setWindow(GLFWwindow *window);

    float getAspectRatio() const;

    void setAspectRatio(float aspectRatio);

private:
    float aspectRatio;
    void initializeOpenGL();
public:

    SimulatorEngine();
    bool initialize();
    bool initialize(int windowWidth, int windowHeight, const string &windowTitle);
    void finalize();
    void drawModel(Model &model, glm::mat4 V);
};

#endif //CPPTEST_SIMULATORENGINE_H
