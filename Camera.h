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
    int currentRoom;
public:
    void setCurrentRoom(int currentRoom);

public:
    Camera(SimulatorEngine &engine1);
    void changePosition(float deltaTime);
    const mat4 &getV() const;
    void setV(const mat4 &V);
    vec3 getPosition();
    void setPosition(vec3 pos);
    vec3 checkInternalCollision(vec3 positionTest ,vec3 position, vec3 viewdirection,int direction, int side, vector<Model*> models, int currentRoom,float delta);
    vec3 checkExternalCollision(vec3 positionTest ,vec3 position, vec3 viewdirection,int direction, int side,vec4 tab[3] ,float delta);

};


#endif //UNUSUALARTGALLERY_CAMERA_H
