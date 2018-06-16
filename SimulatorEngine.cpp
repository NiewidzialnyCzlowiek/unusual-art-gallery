#define GLM_FORCE_RADIANS

#include "SimulatorEngine.h"




SimulatorEngine::SimulatorEngine() {}

bool SimulatorEngine::initialize() {
    return initialize(1024, 576, "Unusual Art Gallery");
}

bool SimulatorEngine::initialize(int windowWidth, int windowHeight, const string &windowTitle) {
    width=windowWidth;
    height=windowHeight;
    aspectRatio = static_cast<float>(windowWidth) / windowHeight;
    P = glm::perspective(50.f * 3.14f / 180.f, aspectRatio, 0.01f, 50.0f);
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
    return true;
}

void SimulatorEngine::finalize() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void SimulatorEngine::initializeOpenGL() {
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwSwapBuffers(window);
}

void SimulatorEngine::drawModel(Model & model, glm::mat4 V, glm::vec3 cameraPos) {
    GLfloat range = 5.5f;
    glm::mat4 M = glm::mat4(1.0f);
    M = glm::translate(M, model.getPosition());
    M = glm::scale(M, model.getScale());

    model.getShader()->use();
    glUniformMatrix4fv(model.getShader()->getUniformLocation("P"),1, GL_FALSE, glm::value_ptr(P));
    glUniformMatrix4fv(model.getShader()->getUniformLocation("V"),1, GL_FALSE, glm::value_ptr(V));
    glUniformMatrix4fv(model.getShader()->getUniformLocation("M"),1, GL_FALSE, glm::value_ptr(M));
    glUniform3fv(model.getShader()->getUniformLocation("playerPosition"),1, glm::value_ptr(cameraPos));
    glUniform1fv(model.getShader()->getUniformLocation("lightRange"),1, &range);
    glUniform3fv(model.getShader()->getUniformLocation("lightPosition"),1, glm::value_ptr(cameraPos));

    glBindVertexArray(model.getVao());
    glDrawArrays(GL_TRIANGLES,0,model.getVertices().size());
    glBindVertexArray(0);
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

GLFWwindow *SimulatorEngine::getWindow() const {
    return window;
}

void SimulatorEngine::setWindow(GLFWwindow *window) {
    SimulatorEngine::window = window;
}

float SimulatorEngine::getAspectRatio() const {
    return aspectRatio;
}

void SimulatorEngine::setAspectRatio(float aspectRatio) {
    SimulatorEngine::aspectRatio = aspectRatio;
}

void SimulatorEngine::drawModels(glm::mat4 V, glm::vec3 cameraPos) {
    cameraPos.x *= -1;
    cameraPos.y *= -1;
    cameraPos.z *= -1;
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    for(Model *m : models) {
        drawModel(*m, V, cameraPos);
    }
    glfwSwapBuffers(window);
}

void SimulatorEngine::addModel(Model *model) {
    models.push_back(model);
}

