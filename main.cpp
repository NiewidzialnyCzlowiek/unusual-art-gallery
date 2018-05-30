#define GLM_FORCE_RADIANS

#include "SimulatorEngine.h"
#include "Camera.h"
#include <GLFW/glfw3.h>

using namespace std;
int main()
{
    SimulatorEngine engine;
    Camera camera(engine);
    if(engine.initialize()) {
        Model house;
        if(!house.loadFromOBJFile("../Models/house.obj")) {
            printf("Cannot load file from .obj file. Exiting");
            return 1;
        }
        house.loadShaders("../Shaders/vshader.vert", nullptr, "../Shaders/fshader.frag");
        house.initializeAndLoadToGraphicsCard();
        glfwSetTime(0);
        while (!glfwWindowShouldClose(engine.getWindow())) {
            camera.changePosition(float(glfwGetTime()));
            glfwSetTime(0);
            engine.drawModel(house, camera.getV());
            glfwPollEvents();
        }
    }
    engine.finalize();
    return 0;
}
