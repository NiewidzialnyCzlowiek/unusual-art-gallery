//
// Created by Asus on 10.05.2018.
//

#ifndef UNUSUALARTGALLERY_CAMERA_H
#define UNUSUALARTGALLERY_CAMERA_H
#include "SimulatorEngine.h"


using namespace glm;


class Camera {
private:
    mat4 V;
    float speed;
    vec3 position;
    vec3 viewDirection;
    float fullAngleX;
    float fullAngleY;
    SimulatorEngine* engine;


public:
    Camera(SimulatorEngine &engine1);
    void changePosition(float deltaTime);
    const mat4 &getV() const;
    void setV(const mat4 &V);
    vec3 getPosition();
    void setPosition(vec3 pos);

};


#endif //UNUSUALARTGALLERY_CAMERA_H
