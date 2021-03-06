#include "Model.h"


Model::Model() {
    loadedToGraphicsMemory = false;
    shader = nullptr;
    texture = nullptr;
    M = glm::mat4(1.f);
    speed = 0.5;
    currentRoom = 0;
    angle = 0;
}

Model::~Model() {
    if(loadedToGraphicsMemory) {
        glDeleteVertexArrays(1,&vao);
        glDeleteBuffers(1,&vboVertices);
        glDeleteBuffers(1,&vboUvs);
        glDeleteBuffers(1,&vboNormals);
    }
    if((shader != nullptr) && shader->isInitialized()) {
        delete shader;
    }
}

bool Model::loadFromOBJFile(const string &path) {
    vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    vector<glm::vec3> temp_vertices;
    vector<glm::vec2> temp_uvs;
    vector<glm::vec3> temp_normals;
    bool loadingUvs = false;
    FILE *file = fopen(path.c_str(), "r");
    if (file == nullptr) {
        return false;
    }
    int res = 65;
    while (res != EOF) {
        char lineHeader[128] = "";
        res = fscanf(file, "%s", lineHeader);
        if (strcmp(lineHeader, "v") == 0) {
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.push_back(vertex);
        } else if (strcmp(lineHeader, "vt") == 0) {
            loadingUvs = true;
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            temp_uvs.push_back(uv);
        } else if (strcmp(lineHeader, "vn") == 0) {
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
        } else if (strcmp(lineHeader, "f") == 0) {
            // std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            if(loadingUvs) {
                int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                                     &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2],
                                     &normalIndex[2]);
                if (matches != 9) {
                    printf("File cannot be imported. Make sure the object was exported as triangles.\n");
                    return false;
                }
            } else {
                int matches = fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0],
                                     &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
                if (matches != 6) {
                    printf("File cannot be imported. Make sure the object was exported as triangles.\n");
                    return false;
                }
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
            if(loadingUvs) {
                uvIndices.push_back(uvIndex[0]);
                uvIndices.push_back(uvIndex[1]);
                uvIndices.push_back(uvIndex[2]);
            }
        }
    }
    for (unsigned int vertexIndex : vertexIndices) {
        glm::vec4 vertex = glm::vec4(temp_vertices[vertexIndex - 1].x,temp_vertices[vertexIndex - 1].y,temp_vertices[vertexIndex - 1].z, 1.f);        
        vertices.push_back(vertex);
    }
    for (unsigned int normalIndex : normalIndices) {
        glm::vec4 normal = glm::vec4(temp_normals[normalIndex - 1].x,temp_normals[normalIndex - 1].y,temp_normals[normalIndex - 1].z, 0.f);
        normals.push_back(normal);
    }
    if(loadingUvs) {
        for (unsigned int uvIndex : uvIndices) {
            glm::vec2 uv = glm::vec2(temp_uvs[uvIndex - 1].x, temp_uvs[uvIndex - 1].y);
            uvs.push_back(uv);
        }
    }
    else {
        for (unsigned int vertexIndex : vertexIndices) {
            uvs.push_back(glm::vec2(0,0));
        }
    }
    return true;
}

GLuint Model::makeBuffer(void *data, int vertexCount, int vertexSize) {
	GLuint handle;

	glGenBuffers(1,&handle);
	glBindBuffer(GL_ARRAY_BUFFER, handle);
	glBufferData(GL_ARRAY_BUFFER, vertexCount*vertexSize, data, GL_STATIC_DRAW);

	return handle;
}

void Model::assignVBOtoAttribute(const char* attributeName, GLuint bufVBO, int vertexSize) {
	if(shader->isInitialized()) {
        GLuint location = shader->getAttribLocation(attributeName);
        glBindBuffer(GL_ARRAY_BUFFER, bufVBO);
        glEnableVertexAttribArray(location);
        glVertexAttribPointer(location,vertexSize,GL_FLOAT, GL_FALSE, 0, nullptr);
    }
}

void Model::initializeAndLoadToGraphicsCard() {
	vboVertices = makeBuffer(vertices.data(), vertices.size(), sizeof(float)*4);
	vboNormals = makeBuffer(normals.data(), vertices.size(), sizeof(float)*4);
    vboUvs = makeBuffer(uvs.data(), uvs.size(), sizeof(float)*2);

	glGenVertexArrays(1,&vao);

	glBindVertexArray(vao);
	assignVBOtoAttribute("vertex", vboVertices, 4);
	assignVBOtoAttribute("normal", vboNormals, 4);
    assignVBOtoAttribute("uv", vboUvs, 2); 
	glBindVertexArray(0);
    
    loadedToGraphicsMemory = true;
}

void Model::loadShaders(const char* vertexShaderFile,const char* geometryShaderFile,const char* fragmentShaderFile) {
    if(shader == nullptr) {
        shader = new ShaderProgram();
    }
    shader->load(vertexShaderFile, geometryShaderFile, fragmentShaderFile);
}

vector<glm::vec4> &Model::getVertices() {
    return vertices;
}

vector<glm::vec2> &Model::getUvs() {
    return uvs;
}

vector<glm::vec4> &Model::getNormals() {
    return normals;
}

ShaderProgram * Model::getShader() {
    return shader;
}

void Model::setShader(ShaderProgram * shaderToSet) {
    shader = shaderToSet;
}

Texture * Model::getTexture() {
    return texture;
}

void Model::setTexture(Texture * textureToSet) {
    texture = textureToSet;
}

GLuint Model::getVao() {
    return vao;
}

GLuint Model::getVboVertices() {
    return vboVertices;
}

GLuint Model::getVboUvs() {
    return vboUvs;
}

GLuint Model::getVboNormals() {
    return vboNormals;
}

const glm::vec3 &Model::getPosition() const {
    return position;
}

void Model::setPosition(const glm::vec3 &position) {
    Model::position = position;
}

const glm::vec3 &Model::getScale() const {
    return scale;
}

void Model::setScale(const glm::vec3 &scale) {
    Model::scale = scale;
}

const glm::vec3 &Model::getRotation() const {
    return Model::rotation;
}

void Model::setRotation(const glm::vec3 &rotation) {
    Model::rotation = rotation;
}

const glm::mat4 &Model::getM() const {
    return Model::M;
}

void Model::setM(const glm::mat4 &M) {
    Model::M = M;
}

void Model::setCollisionCoordinates(glm::vec4 a, glm::vec4 b) {
    roomZone[0]=a;
    roomZone[1]=b;
}

const glm::vec4 *Model::getRoomZone()  {
    return roomZone;
}

void Model::updateCollisionCoordinates() {
    roomZone[0] = M * roomZone[0];
    roomZone[1] = M * roomZone[1];
}

void Model::move(float deltaTime, vector<Model*> & models){
    angle += float(rand()%10-5)/100;

    glm::vec3 positionTest;
    glm::vec3 direction = glm::mat3(rotate(glm::mat4(1.f),angle,glm::vec3(0,1,0))) * glm::vec3(1,0,0);
    positionTest[0] = position[0] + (direction[0] * speed  * deltaTime);
    positionTest[1] = position[1] + (direction[1] * speed  * deltaTime);
    positionTest[2] = position[2] - (direction[2] * speed  * deltaTime);

    if((positionTest.r>  models[currentRoom]->getRoomZone()[0].r and positionTest.r<  models[currentRoom]->getRoomZone()[1].r and
         positionTest.b>  models[currentRoom]->getRoomZone()[0].b and positionTest.b<  models[currentRoom]->getRoomZone()[1].b)){
        position = positionTest;

    }
    else {
        glm::vec3 directionTest = direction;
        int i=0;
        if(!( positionTest.b>  models[currentRoom]->getRoomZone()[0].b and positionTest.b<  models[currentRoom]->getRoomZone()[1].b)){
            directionTest[2] = 0;
            angle += PI/4; 
        }
        if(!(positionTest.r>  models[currentRoom]->getRoomZone()[0].r and positionTest.r<  models[currentRoom]->getRoomZone()[1].r)){
            directionTest[0] = 0;
            angle += PI/4;
        }
        position[0] = position[0] + (directionTest[0] * speed * deltaTime);
        position[1] = position[1] + (directionTest[1] * speed * deltaTime);
        position[2] = position[2] - (directionTest[2] * speed * deltaTime);
        for(Model *m : models) {
            if(positionTest.r>  m->getRoomZone()[0].r and positionTest.r<  m->getRoomZone()[1].r and
                positionTest.b>  m->getRoomZone()[0].b and positionTest.b<  m->getRoomZone()[1].b) {
                currentRoom = i;
                position = positionTest;
            }
            i++;
        }
    }
    M = glm::translate(glm::mat4(1.f),position);
    M = glm::mat4(1.f);
    M = glm::rotate(M, angle, glm::vec3(0.f,1.f,0.f));
    M = glm::translate(glm::mat4(1.f),position);
}
