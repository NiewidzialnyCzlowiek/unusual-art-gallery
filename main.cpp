#define GLM_FORCE_RADIANS

#include "SimulatorEngine.h"
#include "Camera.h"
#include "Setup.cpp"
#include <GLFW/glfw3.h>

SimulatorEngine *enginePointer;

using namespace std;

void windowResize(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height); //Obraz ma być generowany w oknie o tej rozdzielczości
    enginePointer->setAspectRatio(float(width)/height);
    enginePointer->setWidth(width);
    enginePointer->setHeight(height);
}

int main()
{
    SimulatorEngine engine;
    Camera camera(engine);
    enginePointer = &engine;

    if(engine.initialize()) {
        Setup::setupModels(engine);
        glfwSetFramebufferSizeCallback(engine.getWindow(), windowResize);
        glfwSetTime(0);
        while (!glfwWindowShouldClose(engine.getWindow())) {
            camera.changePosition(float(glfwGetTime()));
            glfwSetTime(0);
            engine.drawModels(camera.getV(), camera.getPosition());
            glfwPollEvents();
        }
    }
    engine.finalize();
    return 0;
}
