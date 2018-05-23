#include "SimulatorEngine.h"



float SimulatorEngine::aspectRatio = 1;
GLFWwindow* SimulatorEngine::window = nullptr;

SimulatorEngine::SimulatorEngine() {}

bool SimulatorEngine::initialize() {
    initialize(1024, 576, "Unusual Art Gallery");
}

bool SimulatorEngine::initialize(int windowWidth, int windowHeight, const string &windowTitle) {
    width=windowWidth;
    height=windowHeight;
    aspectRatio = static_cast<float>(windowWidth) / windowHeight;
    if (!glfwInit()) {
        fprintf(stderr, "Cannot initialize GLFW library\n");
        return false;
    }
    window = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), nullptr, nullptr);
    if (!window) {
        fprintf(stderr, "Cannot create window\n");
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Cannot initialize GLEW library\n");
        exit(EXIT_FAILURE);
    }
    glfwSetTime(0);
    initializeOpenGL();
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void SimulatorEngine::finalize() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void SimulatorEngine::initializeOpenGL() {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwSwapBuffers(window);
}



int SimulatorEngine::getWidth() const {
    return width;
}

void SimulatorEngine::setWidth(int width) {
    SimulatorEngine::width = width;
}

int SimulatorEngine::getHeight() const {
    return height;
}

void SimulatorEngine::setHeight(int height) {
    SimulatorEngine::height = height;
}

