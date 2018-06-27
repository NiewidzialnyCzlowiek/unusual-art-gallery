#include "SimulatorEngine.h"

class Setup {
private:
public:
    static void setupModels(SimulatorEngine & engine) {
        auto *corridor12 = new Model();
        auto *corridor14 = new Model();
        auto *corridor23 = new Model();
        auto *corridor34 = new Model();
        auto *room1 = new Model();
        auto *room2 = new Model();
        auto *room3 = new Model();
        auto *room4 = new Model();
        auto *shader = new ShaderProgram();
        auto *roomtexture = new Texture();

        shader->load("./Shaders/singleLightVertSh.vert", nullptr, "./Shaders/singleLightFragSh.frag");

        roomtexture->loadColorTexture("./Textures/white.png");
        roomtexture->loadSpecularTexture("./Textures/concrete.png");
        
        if(room1->loadFromOBJFile("./Models/room.obj")) {}
        room1->setShader(shader);
        room1->initializeAndLoadToGraphicsCard();
        glm::mat4 M = glm::mat4(1.f);
        room1->setCollisionCoordinates(glm::vec4(4.f,0.f,4.f,1.f),glm::vec4(-4.f,0.f,4.f,1.f),glm::vec4(4.f,0.f,-4.f,1.f));
        room1->setM(M);
        room1->setTexture(roomtexture);

        if(corridor12->loadFromOBJFile("./Models/corridor.obj")) {}
        corridor12->setShader(shader);
        corridor12->initializeAndLoadToGraphicsCard();
        M = glm::mat4(1.f);
        M = glm::translate(M, glm::vec3(6.f, 0.f, 0.f));
        corridor12->setCollisionCoordinates(glm::vec4(2.f,0.f,1.f,1.f),glm::vec4(-2.f,0.f,1.f,1.f),glm::vec4(2.f,0.f,-1.f,1.f));
        corridor12->setM(M);
        corridor12->setTexture(roomtexture);

        if(room2->loadFromOBJFile("./Models/room.obj")) {}
        room2->setShader(shader);
        room2->initializeAndLoadToGraphicsCard();
        M = glm::mat4(1.f);
        M = glm::translate(M, glm::vec3(0,0,-12));
        M = glm::rotate(M, -3.14f/2, glm::vec3(0,1,0));
        room2->setCollisionCoordinates(glm::vec4(4.f,0.f,4.f,1.f),glm::vec4(-4.f,0.f,4.f,1.f),glm::vec4(4.f,0.f,-4.f,1.f));
        room2->setM(M);
        room2->setTexture(roomtexture);

        if(corridor23->loadFromOBJFile("./Models/corridor.obj")) {}
        corridor23->setShader(shader);
        corridor23->initializeAndLoadToGraphicsCard();
        M = glm::mat4(1.f);
        M = glm::translate(M, glm::vec3(6.f, 0.f, -12.f));
        corridor23->setCollisionCoordinates(glm::vec4(2.f,0.f,0.9f,1.f),glm::vec4(-2.f,0.f,0.9f,1.f),glm::vec4(2.f,0.f,-0.9f,1.f));
        corridor23->setM(M);
        corridor23->setTexture(roomtexture);
        
        if(room3->loadFromOBJFile("./Models/room.obj")) {}
        room3->setShader(shader);
        room3->initializeAndLoadToGraphicsCard();
        M = glm::mat4(1.f);
        M = glm::translate(M, glm::vec3(12,0,-12));
        M = glm::rotate(M, -3.14f, glm::vec3(0,1,0));
        room3->setCollisionCoordinates(glm::vec4(4.f,0.f,4.f,1.f),glm::vec4(-4.f,0.f,4.f,1.f),glm::vec4(4.f,0.f,-4.f,1.f));
        room3->setM(M);
        room3->setTexture(roomtexture);

        if(corridor34->loadFromOBJFile("./Models/corridor.obj")) {}
        corridor34->setShader(shader);
        corridor34->initializeAndLoadToGraphicsCard();
        M = glm::mat4(1.f);
        M = glm::translate(M, glm::vec3(12.f, 0.f, -6.f));
        M = glm::rotate(M, 3.14f/2, glm::vec3(0.f, 1, 0));
        corridor34->setCollisionCoordinates(glm::vec4(2.f,0.f,0.9f,1.f),glm::vec4(-2.f,0.f,0.9f,1.f),glm::vec4(2.f,0.f,-0.9f,1.f));
        corridor34->setM(M);
        corridor34->setTexture(roomtexture);

        if(room4->loadFromOBJFile("./Models/room.obj")) {}
        room4->setShader(shader);
        room4->initializeAndLoadToGraphicsCard();
        M = glm::mat4(1.f);
        M = glm::translate(M, glm::vec3(12,0,0));
        M = glm::rotate(M, 3.14f/2, glm::vec3(0,1,0));
        room4->setCollisionCoordinates(glm::vec4(4.f,0.f,4.f,1.f),glm::vec4(-4.f,0.f,4.f,1.f),glm::vec4(4.f,0.f,-4.f,1.f));
        room4->setM(M);
        room4->setTexture(roomtexture);

        if(corridor14->loadFromOBJFile("./Models/corridor.obj")) {}
        corridor14->setShader(shader);
        corridor14->initializeAndLoadToGraphicsCard();
        M = glm::mat4(1.f);
        M = glm::rotate(M, 3.14f/2, glm::vec3(0.f, 1, 0));
        M = glm::translate(M, glm::vec3(6.f, 0.f, 0.f));
        corridor14->setCollisionCoordinates(glm::vec4(2.f,0.f,0.9f,1.f),glm::vec4(-2.f,0.f,0.9f,1.f),glm::vec4(2.f,0.f,-0.9f,1.f));
        corridor14->setM(M);
        corridor14->setTexture(roomtexture);
        

        


        engine.addModel(room1);
        engine.addModel(corridor12);
        engine.addModel(room2);
        engine.addModel(corridor23);
        engine.addModel(room3);
        engine.addModel(corridor34);
        engine.addModel(room4);
        engine.addModel(corridor14);

    }
};
