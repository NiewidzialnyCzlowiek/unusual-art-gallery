//
// Created by Asus on 10.05.2018.
//


#include "Camera.h"


Camera::Camera(SimulatorEngine &engine1) {
    engine = &engine1;
    position = vec3(0.f,-0.5f,0.f);
    viewDirection = vec3(0.f,0.f,1.f);
    V = glm::lookAt(position, viewDirection, glm::vec3(0.f,1.f,0.f));
    speed = 1;
    fullAngleX = 0;
    fullAngleY = 0;

}

void Camera::changePosition(float deltaTime) {
    int direction = 0,side = 0;
    if(glfwGetKey(SimulatorEngine::window,GLFW_KEY_W) == 1)direction = 1;
    else if(glfwGetKey(SimulatorEngine::window,GLFW_KEY_S) == 1)direction = -1;
    if(glfwGetKey(SimulatorEngine::window,GLFW_KEY_A) == 1)side = -1;
    else if(glfwGetKey(SimulatorEngine::window,GLFW_KEY_D) == 1)side = 1;
    double x,y;
    float x1,y1;
    glfwGetCursorPos(SimulatorEngine::window,&x,&y);
    x1 = static_cast<float>(x);
    y1 = static_cast<float>(y);

    if(glfwGetKey(SimulatorEngine::window,GLFW_KEY_X) == 1){
        x1 = engine->getWidth() / 2;
        y1 = engine->getHeight() / 2;
    }
    else {
        glfwSetCursorPos(SimulatorEngine::window, engine->getWidth() / 2, engine->getHeight() / 2);
    }

    V = lookAt(vec3(0, 0, 0), vec3(0, 0, 1), vec3(0, 1, 0));
    x1 = (x1 - engine->getWidth() / 2);
    x1 = x1 / 750;
    y1 = (y1 - engine->getHeight() / 2);
    y1 = y1 / 750;

    if (fullAngleY > 0.3 && y1 > 0)y1 = 0;
    if (fullAngleY < -1 && y1 < 0)y1 = 0;
    fullAngleX+= x1;
    fullAngleY+= y1;




    viewDirection = mat3(rotate(mat4(1.f),x1,vec3(0,1,0))) * viewDirection;

    position[0] = position[0] + (viewDirection[0] * speed * direction * deltaTime);
    position[1] = position[1] + (viewDirection[1] * speed * direction * deltaTime);
    position[2] = position[2] - (viewDirection[2] * speed * direction * deltaTime);
    position[0] = position[0] + (viewDirection[2] * speed * side * deltaTime);
    position[1] = position[1] + (viewDirection[1] * speed * side * deltaTime);
    position[2] = position[2] + (viewDirection[0] * speed * side * deltaTime);


    V=rotate(V,fullAngleX,vec3(0,1,0));
    V=rotate(V,-fullAngleY,vec3(viewDirection[2],0,viewDirection[0]));
    V=translate(V,position);

    setV(V);

}

const mat4 &Camera::getV() const {
    return V;
}

void Camera::setV(const mat4 &V) {
    Camera::V = V;
}
