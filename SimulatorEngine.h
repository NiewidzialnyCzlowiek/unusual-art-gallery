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
    float aspectRatio;
    void initializeOpenGL();
    vector<Model*> models;
    glm::mat4 P;

public:
    GLFWwindow *getWindow() const;

    void setWindow(GLFWwindow *window);

    float getAspectRatio() const;

    void setAspectRatio(float aspectRatio);

    SimulatorEngine();

    bool initialize();

    bool initialize(int windowWidth, int windowHeight, const string &windowTitle);

    void finalize();

    void drawModel(Model &model, glm::mat4 V, glm::vec3 cameraPos);

    void drawModels(glm::mat4 V, glm::vec3 cameraPos);

    void addModel(Model * model);
};

#endif //CPPTEST_SIMULATORENGINE_H
