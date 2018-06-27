#include "SimulatorEngine.h"

class Setup {
private:
public:
    static void setupModels(SimulatorEngine & engine) {
        auto *cube = new Model();
        auto *house = new Model();
        auto *hand = new Model();
        auto *shader = new ShaderProgram();
        auto *cubetexture = new Texture();


        if(cube->loadFromOBJFile("../Models/cube.obj")) {}
        if(house->loadFromOBJFile("../Models/cube.obj")) {}


        shader->load("../Shaders/singleLightVertSh.vert", nullptr, "../Shaders/singleLightFragSh.frag");

        cube->setShader(shader);
            house->setShader(shader);


        cubetexture->loadColorTexture("../Models/drewno.png");
        cubetexture->loadSpecularTexture("../Models/drewno.png");


        cube->initializeAndLoadToGraphicsCard();
        house->initializeAndLoadToGraphicsCard();


        glm::mat4 MercedesM = glm::mat4(1.f);
        //MercedesM = glm::translate(MercedesM, glm::vec3(0.f, 0.f, 0.f));
        MercedesM = glm::scale(MercedesM, glm::vec3(1.f, 1.f, 1.f));

        cube->setWspolrzedne(glm::vec4(1.f,0.f,1.f,1.f),glm::vec4(-1.f,0.f,1.f,1.f),glm::vec4(1.f,0.f,-1.f,1.f));
            cube->setM(MercedesM);
            glm::mat4 M = glm::mat4(1.f);
            M = glm::translate(M, glm::vec3(2.f, 0.f, 0.f));
            M = glm::scale(M, glm::vec3(1.f, 1.f, 1.f));

            house->setWspolrzedne(glm::vec4(1.f,0.f,1.f,1.f),glm::vec4(-1.f,0.f,1.f,1.f),glm::vec4(1.f,0.f,-1.f,1.f));
            house->setM(M);


        cube->setTexture(cubetexture);
            house->setTexture(cubetexture);


        engine.addModel(cube);
        engine.addModel(house);

    }
};