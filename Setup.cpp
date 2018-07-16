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
        auto *floortexture = new Texture();

        shader->load("./Shaders/singleLightVertSh.vert", nullptr, "./Shaders/singleLightFragSh.frag");

        roomtexture->loadColorTexture("./Textures/white.png");
        roomtexture->loadSpecularTexture("./Textures/concrete.png");
        floortexture->loadColorTexture("./Textures/floor.png");
        floortexture->loadSpecularTexture("./Textures/floor.png");

        if(room1->loadFromOBJFile("./Models/room.obj")) {}
        room1->setShader(shader);
        room1->initializeAndLoadToGraphicsCard();
        glm::mat4 M = glm::mat4(1.f);
        room1->setCollisionCoordinates(glm::vec4(-3.9f,0.f,-3.9f,1.f),glm::vec4(3.9f,0.f,3.9f,1.f));
        room1->setM(M);
        room1->setTexture(roomtexture);

        if(corridor12->loadFromOBJFile("./Models/corridor.obj")) {}
        corridor12->setShader(shader);
        corridor12->initializeAndLoadToGraphicsCard();
        M = glm::mat4(1.f);
        M = glm::rotate(M, PI/2, glm::vec3(0.f, 1, 0));
        M = glm::translate(M, glm::vec3(6.f, 0.f, 0.f));
        corridor12->setCollisionCoordinates(glm::vec4(-0.9f,0.f,-8.1f,1.f),glm::vec4(0.9f,0.f,-3.9f,1.f));
        corridor12->setM(M);
        corridor12->setTexture(roomtexture);

        if(room2->loadFromOBJFile("./Models/room.obj")) {}
        room2->setShader(shader);
        room2->initializeAndLoadToGraphicsCard();
        M = glm::mat4(1.f);
        M = glm::translate(M, glm::vec3(0,0,-12));
        M = glm::rotate(M, -PI/2, glm::vec3(0,1,0));
        room2->setCollisionCoordinates(glm::vec4(-3.9f,0.f,-15.9f,1.f),glm::vec4(3.9f,0.f,-8.1f,1.f));
        room2->setM(M);
        room2->setTexture(roomtexture);

        if(corridor23->loadFromOBJFile("./Models/corridor.obj")) {}
        corridor23->setShader(shader);
        corridor23->initializeAndLoadToGraphicsCard();
        M = glm::mat4(1.f);
        M = glm::translate(M, glm::vec3(6.f, 0.f, -12.f));
        corridor23->setCollisionCoordinates(glm::vec4(3.9f,0.f,-12.9f,1.f),glm::vec4(8.1f,0.f,-11.1f,1.f));
        corridor23->setM(M);
        corridor23->setTexture(roomtexture);
        
        if(room3->loadFromOBJFile("./Models/room.obj")) {}
        room3->setShader(shader);
        room3->initializeAndLoadToGraphicsCard();
        M = glm::mat4(1.f);
        M = glm::translate(M, glm::vec3(12,0,-12));
        M = glm::rotate(M, -PI, glm::vec3(0,1,0));
        room3->setCollisionCoordinates(glm::vec4(8.1f,0.f,-15.9f,1.f),glm::vec4(15.9f,0.f,-8.1f,1.f));
        room3->setM(M);
        room3->setTexture(roomtexture);

        if(corridor34->loadFromOBJFile("./Models/corridor.obj")) {}
        corridor34->setShader(shader);
        corridor34->initializeAndLoadToGraphicsCard();
        M = glm::mat4(1.f);
        M = glm::translate(M, glm::vec3(12.f, 0.f, -6.f));
        M = glm::rotate(M, PI/2, glm::vec3(0.f, 1, 0));
        corridor34->setCollisionCoordinates(glm::vec4(11.1f,0.f,-8.1f,1.f),glm::vec4(12.9f,0.f,-3.9f,1.f));
        corridor34->setM(M);
        corridor34->setTexture(roomtexture);

        if(room4->loadFromOBJFile("./Models/room.obj")) {}
        room4->setShader(shader);
        room4->initializeAndLoadToGraphicsCard();
        M = glm::mat4(1.f);
        M = glm::translate(M, glm::vec3(12,0,0));
        M = glm::rotate(M, PI/2, glm::vec3(0,1,0));
        room4->setCollisionCoordinates(glm::vec4(8.1f,0.f,-3.9f,1.f),glm::vec4(15.9f,0.f,3.9f,1.f));
        room4->setM(M);
        room4->setTexture(roomtexture);

        if(corridor14->loadFromOBJFile("./Models/corridor.obj")) {}
        corridor14->setShader(shader);
        corridor14->initializeAndLoadToGraphicsCard();
        M = glm::mat4(1.f);
        M = glm::translate(M, glm::vec3(6.f, 0.f, 0.f));
        corridor14->setCollisionCoordinates(glm::vec4(3.9f,0.f,-0.9f,1.f),glm::vec4(8.1f,0.f,0.9f,1.f));
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






        // auto *tomasz = new Texture();
        // tomasz->loadColorTexture("./Textures/Tomasz.png");
        // tomasz->loadSpecularTexture("./Textures/Tomasz.png");
        // auto *baymax = new Model();
        // if(baymax->loadFromOBJFile("./Models/cube.obj"));
        // baymax->setShader(shader);
        // baymax->initializeAndLoadToGraphicsCard();
        // M = glm::mat4(1.f);
        // M = glm::scale(M, glm::vec3(0.5,0.5,0.5));
        // baymax->setCollisionCoordinates(glm::vec4(-0.5f,0.f,-0.5f,1.f),glm::vec4(0.5f,0.f,0.5f,1.f));
        // baymax->setM(M);
        // baymax->setPosition(glm::vec3(0,0,0));
        // baymax->setTexture(tomasz);

        auto *landlordtex = new Texture();
        landlordtex->loadColorTexture("./Textures/landlord.png");
        landlordtex->loadSpecularTexture("./Textures/landlord.png");
        auto *landlord1 = new Model();
        if(landlord1->loadFromOBJFile("./Models/landlord.obj"));
        landlord1->setShader(shader);
        landlord1->initializeAndLoadToGraphicsCard();
        M = glm::mat4(1.f);
        M = glm::translate(M, glm::vec3(-2,-1,0));
        landlord1->setCollisionCoordinates(glm::vec4(-0.5f,0.f,-0.5f,1.f),glm::vec4(0.5f,0.f,0.5f,1.f));
        landlord1->setM(M);
        landlord1->setPosition(glm::vec3(-2,-1,0));
        landlord1->setTexture(landlordtex);

        auto *landlordkingtex = new Texture();
        landlordkingtex->loadColorTexture("./Textures/landlordking.png");
        landlordkingtex->loadSpecularTexture("./Textures/landlordking.png");
        auto *landlord2 = new Model();
        if(landlord2->loadFromOBJFile("./Models/landlord.obj"));
        landlord2->setShader(shader);
        landlord2->initializeAndLoadToGraphicsCard();
        M = glm::mat4(1.f);
        M = glm::translate(M, glm::vec3(0,-1,2));
        landlord2->setCollisionCoordinates(glm::vec4(-0.5f,0.f,-0.5f,1.f),glm::vec4(0.5f,0.f,0.5f,1.f));
        landlord2->setM(M);
        landlord2->setPosition(glm::vec3(0,-1,2));
        landlord2->setTexture(landlordkingtex);

        auto *landlord3 = new Model();
        if(landlord3->loadFromOBJFile("./Models/landlord.obj"));
        landlord3->setShader(shader);
        landlord3->initializeAndLoadToGraphicsCard();
        M = glm::mat4(1.f);
        M = glm::translate(M, glm::vec3(2,-1,2));
        landlord3->setCollisionCoordinates(glm::vec4(-0.5f,0.f,-0.5f,1.f),glm::vec4(0.5f,0.f,0.5f,1.f));
        landlord3->setM(M);
        landlord3->setPosition(glm::vec3(2,-1,2));
        landlord3->setTexture(landlordtex);

        engine.addMovable(landlord1);
        engine.addMovable(landlord2);
        engine.addMovable(landlord3);
        //engine.addMovable(baymax);






        auto *floor1 = new Model();
        if(floor1->loadFromOBJFile("./Models/floor.obj"));
        floor1->setShader(shader);
        floor1->initializeAndLoadToGraphicsCard();
        floor1->setTexture(floortexture);
        M = glm::mat4(1.f);
        M = glm::translate(M, glm::vec3(1,0,-1));
        floor1->setM(M);

        auto *floor2 = new Model();
        if(floor2->loadFromOBJFile("./Models/floor.obj"));
        floor2->setShader(shader);
        floor2->initializeAndLoadToGraphicsCard();
        floor2->setTexture(floortexture);
        M = glm::mat4(1.f);
        M = glm::translate(M, glm::vec3(11,0,-1));
        floor2->setM(M);

        auto *floor3 = new Model();
        if(floor3->loadFromOBJFile("./Models/floor.obj"));
        floor3->setShader(shader);
        floor3->initializeAndLoadToGraphicsCard();
        floor3->setTexture(floortexture);
        M = glm::mat4(1.f);
        M = glm::translate(M, glm::vec3(11,0,-11));
        floor3->setM(M);

        auto *floor4 = new Model();
        if(floor4->loadFromOBJFile("./Models/floor.obj"));
        floor4->setShader(shader);
        floor4->initializeAndLoadToGraphicsCard();
        floor4->setTexture(floortexture);
        M = glm::mat4(1.f);
        M = glm::translate(M, glm::vec3(1,0,-11));
        floor4->setM(M);

        auto *kwadrattex = new Texture();
        kwadrattex->loadColorTexture("./Textures/kwadrat.png");
        kwadrattex->loadSpecularTexture("./Textures/kwadrat.png");
        auto *kwadrat = new Model();
        if(kwadrat->loadFromOBJFile("./Models/plane.obj"));
        kwadrat->setShader(shader);
        kwadrat->initializeAndLoadToGraphicsCard();
        kwadrat->setTexture(kwadrattex);
        M = glm::mat4(1.f);
        M = glm::translate(M, glm::vec3(0,0,3.99));
        M = glm::scale(M, glm::vec3(0.75,0.75,1));
        M = glm::rotate(M, PI, glm::vec3(0,1,0));
        kwadrat->setM(M);

        auto *grunwaldtex = new Texture();
        grunwaldtex->loadColorTexture("./Textures/grunwald.png");
        grunwaldtex->loadSpecularTexture("./Textures/grunwald.png");
        auto *grunwald = new Model();
        if(grunwald->loadFromOBJFile("./Models/plane.obj"));
        grunwald->setShader(shader);
        grunwald->initializeAndLoadToGraphicsCard();
        grunwald->setTexture(grunwaldtex);
        M = glm::mat4(1.f);
        M = glm::translate(M, glm::vec3(-3.99,0,0));
        M = glm::scale(M, glm::vec3(1,0.75,2.3 * 0.75));
        M = glm::rotate(M, PI/2, glm::vec3(0,1,0));
        M = glm::rotate(M, PI, glm::vec3(0,0,-1));
        grunwald->setM(M);

        auto *abstrakt1tex = new Texture();
        abstrakt1tex->loadColorTexture("./Textures/abstrakt1.png");
        abstrakt1tex->loadSpecularTexture("./Textures/abstrakt1.png");
        auto *abstrakt1 = new Model();
        if(abstrakt1->loadFromOBJFile("./Models/plane.obj"));
        abstrakt1->setShader(shader);
        abstrakt1->initializeAndLoadToGraphicsCard();
        abstrakt1->setTexture(abstrakt1tex);
        M = glm::mat4(1.f);
        M = glm::translate(M, glm::vec3(-3.99,0,-12));
        M = glm::rotate(M, PI/2, glm::vec3(0,1,0));
        M = glm::rotate(M, PI, glm::vec3(0,0,-1));
        M = glm::scale(M, glm::vec3(0.75*1200.f/803,0.75,1));
        abstrakt1->setM(M);

        auto *abstrakt2tex = new Texture();
        abstrakt2tex->loadColorTexture("./Textures/abstrakt2.png");
        abstrakt2tex->loadSpecularTexture("./Textures/abstrakt2.png");
        auto *abstrakt2 = new Model();
        if(abstrakt2->loadFromOBJFile("./Models/plane.obj"));
        abstrakt2->setShader(shader);
        abstrakt2->initializeAndLoadToGraphicsCard();
        abstrakt2->setTexture(abstrakt2tex);
        M = glm::mat4(1.f);
        M = glm::translate(M, glm::vec3(0,0,-15.99));
        M = glm::scale(M, glm::vec3(0.75*930.f/347,0.75,1));
        abstrakt2->setM(M);

        auto *abstrakt3tex = new Texture();
        abstrakt3tex->loadColorTexture("./Textures/abstrakt3.png");
        abstrakt3tex->loadSpecularTexture("./Textures/abstrakt3.png");
        auto *abstrakt3 = new Model();
        if(abstrakt3->loadFromOBJFile("./Models/plane.obj"));
        abstrakt3->setShader(shader);
        abstrakt3->initializeAndLoadToGraphicsCard();
        abstrakt3->setTexture(abstrakt3tex);
        M = glm::mat4(1.f);
        M = glm::translate(M, glm::vec3(12,0,3.99));
        M = glm::scale(M, glm::vec3(0.75*640.f/490,0.75,1));
        M = glm::rotate(M, PI, glm::vec3(0,1,0));
        abstrakt3->setM(M);

        auto *guernicatex = new Texture();
        guernicatex->loadColorTexture("./Textures/guernica.png");
        guernicatex->loadSpecularTexture("./Textures/guernica.png");
        auto *guernica = new Model();
        if(guernica->loadFromOBJFile("./Models/plane.obj"));
        guernica->setShader(shader);
        guernica->initializeAndLoadToGraphicsCard();
        guernica->setTexture(guernicatex);
        M = glm::mat4(1.f);
        M = glm::translate(M, glm::vec3(15.99,0,0));
        M = glm::scale(M, glm::vec3(1,0.75,0.75*1100.f/500));
        M = glm::rotate(M, -PI/2, glm::vec3(0,1,0));
        M = glm::rotate(M, PI, glm::vec3(0,0,-1));
        guernica->setM(M);

        auto *carbon = new Texture();
        carbon->loadColorTexture("./Textures/carbon.png");
        carbon->loadSpecularTexture("./Textures/carbon.png");
        auto *diamondcube = new Model();
        if(diamondcube->loadFromOBJFile("./Models/diamondcube.obj"));
        diamondcube->setShader(shader);
        diamondcube->initializeAndLoadToGraphicsCard();
        diamondcube->setTexture(carbon);
        M = glm::mat4(1.f);
        M = glm::translate(M, glm::vec3(12,0,-12));
        M = glm::scale(M, glm::vec3(0.67,0.67,0.67));
        M = glm::rotate(M, PI/4, glm::vec3(1,1,0));
        diamondcube->setM(M);

        engine.addNonMovable(kwadrat);
        engine.addNonMovable(grunwald);
        engine.addNonMovable(abstrakt1);
        engine.addNonMovable(abstrakt2);
        engine.addNonMovable(abstrakt3);
        engine.addNonMovable(guernica);
        engine.addNonMovable(diamondcube);

        engine.addNonMovable(floor1);
        engine.addNonMovable(floor2);
        engine.addNonMovable(floor3);
        engine.addNonMovable(floor4);
    }
};
