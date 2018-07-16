#ifndef CPPTEST_SIMULATORENGINE_H
#define CPPTEST_SIMULATORENGINE_H


#include "Model.h"

using namespace std;

class SimulatorEngine {
private:
    int width;
    int height;
    GLFWwindow * window;
    float aspectRatio;
    void initializeOpenGL();
    vector<Model*> models;
    vector<Model*> movables;
    vector<Model*> nonMovables;
    glm::mat4 P;
    glm::vec3 lights[4];

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

    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);

    const vector<Model *> &getModels() const;

    void addMovable(Model * movable);

    const vector<Model *> &getMovables() const;

    const vector<Model *> &getNonMovables() const;

    void moveMovables(float deltaTime) ;

    void addNonMovable(Model * nonMovable);

};

#endif //CPPTEST_SIMULATORENGINE_H
