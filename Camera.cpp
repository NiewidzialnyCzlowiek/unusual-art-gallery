//
// Created by Asus on 10.05.2018.
//


#include "Camera.h"


Camera::Camera(SimulatorEngine &engine1) {
    engine = &engine1;
    position = vec3(0.f,0.f,0.0f);
    viewDirection = vec3(0.f,0.f,1.f);
    V = glm::lookAt(position, viewDirection, glm::vec3(0.f,1.f,0.f));
    speed = 2;
    fullAngleX = 0;
    fullAngleY = 0;
    currentRoom = 0;

}

void Camera::changePosition(float deltaTime) {
    int direction = 0,side = 0;
    if(glfwGetKey(engine->getWindow(),GLFW_KEY_W) == 1)direction = -1;
    else if(glfwGetKey(engine->getWindow(),GLFW_KEY_S) == 1)direction = 1;
    if(glfwGetKey(engine->getWindow(),GLFW_KEY_A) == 1)side = 1;
    else if(glfwGetKey(engine->getWindow(),GLFW_KEY_D) == 1)side = -1;
    double x,y;
    float x1,y1;
    glfwGetCursorPos(engine->getWindow(),&x,&y);
    x1 = static_cast<float>(x);
    y1 = static_cast<float>(y);

    glfwSetCursorPos(engine->getWindow(),engine->getWidth() / 2,engine->getHeight() / 2);

    V = lookAt(vec3(0, 0, 0), vec3(0, 0, 1), vec3(0, 1, 0));
    x1 = (x1 - engine->getWidth() / 2);
    x1 = x1 / 750;
    y1 = (y1 - engine->getHeight() / 2);
    y1 = y1 / 750;

    if (fullAngleY > 0.3 && y1 > 0)y1 = 0;
    if (fullAngleY < -1 && y1 < 0)y1 = 0;
    fullAngleX+= x1;
    fullAngleY+= y1;

    vec3 positionTest;



    viewDirection = mat3(rotate(mat4(1.f),x1,vec3(0,1,0))) * viewDirection;

    positionTest[0] = position[0] + (viewDirection[0] * speed * direction * deltaTime);
    positionTest[1] = position[1] + (viewDirection[1] * speed * direction * deltaTime);
    positionTest[2] = position[2] - (viewDirection[2] * speed * direction * deltaTime);
    positionTest[0] = positionTest[0] + (viewDirection[2] * speed * side * deltaTime);
    positionTest[1] = positionTest[1] + (viewDirection[1] * speed * side * deltaTime);
    positionTest[2] = positionTest[2] + (viewDirection[0] * speed * side * deltaTime);


    V=rotate(V,fullAngleX,vec3(0,1,0));
    V=rotate(V,-fullAngleY,vec3(viewDirection[2],0,viewDirection[0]));


    positionTest = checkInternalCollision(position,positionTest,viewDirection, direction, side, engine->getModels(),currentRoom,deltaTime);

   for(Model *m : engine->getMovables()) {
       positionTest = checkExternalCollision(position,positionTest,viewDirection, direction, side, m, deltaTime);

   }

    position = positionTest;
    positionTest.r*=-1;
    positionTest.g*=-1;
    positionTest.b*=-1;

    // V=translate(V,position);
    V=translate(V,positionTest);

}

const mat4 &Camera::getV() const {
    return V;
}

void Camera::setV(const mat4 &V) {
    Camera::V = V;
}

vec3 Camera::getPosition() {
    return position;
}

void Camera::setPosition(vec3 pos) {
    position = pos;
}

vec3 Camera::checkInternalCollision(vec3 position,vec3 positionTest, vec3 viewdirection, int direction, int side,vector<Model *> models, int currentRoom, float delta) {
    if((positionTest.r>  models[currentRoom]->getRoomZone()[0].r and positionTest.r<  models[currentRoom]->getRoomZone()[1].r and
         positionTest.b>  models[currentRoom]->getRoomZone()[0].b and positionTest.b<  models[currentRoom]->getRoomZone()[1].b)){


        return positionTest;

    }
    else {
        vec3 directionTest = viewdirection;
        int i=0;
            for(Model *m : models) {

                if(positionTest.r>  m->getRoomZone()[0].r and positionTest.r<  m->getRoomZone()[1].r and
                   positionTest.b>  m->getRoomZone()[0].b and positionTest.b<  m->getRoomZone()[1].b) {
                    this->setCurrentRoom(i);
                    return positionTest;
                }
                i++;
            }
        if(!( positionTest.b>  models[currentRoom]->getRoomZone()[0].b and positionTest.b<  models[currentRoom]->getRoomZone()[1].b)){
            directionTest[2] = 0;

        }
        if(!(positionTest.r>  models[currentRoom]->getRoomZone()[0].r and positionTest.r<  models[currentRoom]->getRoomZone()[1].r)){
            directionTest[0] = 0;


        }


        position[0] = position[0] + (directionTest[0] * speed * direction * delta);
        position[1] = position[1] + (directionTest[1] * speed * direction * delta);
        position[2] = position[2] - (directionTest[2] * speed * direction * delta);
        directionTest=viewdirection;
        if(!(positionTest.b>  models[currentRoom]->getRoomZone()[0].b and positionTest.b<  models[currentRoom]->getRoomZone()[1].b)){

            directionTest[0]=0;
        }
        if(!(positionTest.r>  models[currentRoom]->getRoomZone()[0].r and positionTest.r<  models[currentRoom]->getRoomZone()[1].r)){
            directionTest[2]=0;
        }
        position[0] = position[0] + (directionTest[2] * speed * side * delta);
        position[1] = position[1] + (directionTest[1] * speed * side * delta);
        position[2] = position[2] + (directionTest[0] * speed * side * delta);

        return position;

        }

    }

void Camera::setCurrentRoom(int currentRoom) {
    Camera::currentRoom = currentRoom;
}

vec3 Camera::checkExternalCollision(vec3 position,vec3 positionTest, vec3 viewdirection, int direction, int side, Model * m, float delta) {
        vec4 tab[2];
        tab[0] = m->getRoomZone()[0];
        tab[1] = m->getRoomZone()[1];
        mat4 M = translate(mat4(1.f), m->getPosition());
        tab[0] = M * tab[0];
        tab[1] = M * tab[1];

        if(!(positionTest.r>  tab[0].r and positionTest.r<  tab[1].r and
            positionTest.b>  tab[0].b and positionTest.b<  tab[1].b)){

        return positionTest;

    }
    else {

        vec3 directionTest = viewdirection;

        if(!( position.b>  tab[0].b and position.b<  tab[1].b)){
            directionTest[2]=0;

        }
        if(!(position.r>  tab[0].r and position.r<  tab[1].r)){
            directionTest[0]=0;
        }


        position[0] = position[0] + (directionTest[0] * speed * direction * delta);
        position[1] = position[1] + (directionTest[1] * speed * direction * delta);
        position[2] = position[2] - (directionTest[2] * speed * direction * delta);
        directionTest=viewdirection;
        if(!(position.b>  tab[0].b and position.b<  tab[1].b)){

            directionTest[0]=0;
        }
        if(!(position.r>  tab[0].r and position.r<  tab[1].r)){
            directionTest[2]=0;
        }
        position[0] = position[0] + (directionTest[2] * speed * side * delta);
        position[1] = position[1] + (directionTest[1] * speed * side * delta);
        position[2] = position[2] + (directionTest[0] * speed * side * delta);

        return position;

    }

}

