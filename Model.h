#ifndef UNUSUALARTGALLERY_MODEL_H
#define UNUSUALARTGALLERY_MODEL_H

#include <vector>
#include <string>
#include "ShaderProgram.h"
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <detail/type_mat.hpp>
#include <gtc/matrix_transform.hpp>
using namespace std;

class Model {
private:
    vector<glm::vec4> vertices;
    vector<glm::vec2> uvs;
    vector<glm::vec4> normals;
    glm::vec3 position;
    glm::vec3 scale;
    ShaderProgram *shader;
    GLuint vao;
    GLuint vboVertices; //Uchwyt na bufor VBO przechowujący tablicę współrzędnych wierzchołków
    GLuint vboColors;  //Uchwyt na bufor VBO przechowujący tablicę kolorów
    GLuint vboNormals;
    bool loadedToGraphicsMemory;
    GLuint makeBuffer(void *data, int vertexCount, int vertexSize);
    void assignVBOtoAttribute(const char* attributeName, GLuint bufVBO, int vertexSize);
    
public:
    Model();

    ~Model();

    bool loadFromOBJFile(const string &path);

    void loadShaders(const char* vertexShaderFile,const char* geometryShaderFile,const char* fragmentShaderFile);

    void initializeAndLoadToGraphicsCard();

    vector<glm::vec4> & getVertices();

    vector<glm::vec2> & getUvs();

    vector<glm::vec4> & getNormals();

    ShaderProgram * getShader();

    void setShader(ShaderProgram * shaderToSet);

    GLuint getVao();

    GLuint getVboVertices();

    GLuint getVboColors();

    GLuint getVboNormals();

    const glm::vec3 &getPosition() const;

    void setPosition(const glm::vec3 &position);

    const glm::vec3 &getScale() const;

    void setScale(const glm::vec3 &scale);

};

#endif //UNUSUALARTGALLERY_MODEL_H
