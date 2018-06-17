#include "Texture.h"

Texture::Texture() {
    colorTexture = -1;
    normalMap = -1;
    specularTexture = -1;
}

Texture::~Texture() {
    if(colorTexture != -1)
        glDeleteTextures(1, &colorTexture);
    if(normalMap != -1)
        glDeleteTextures(1, &normalMap);
    if(specularTexture != -1)
        glDeleteTextures(1, &specularTexture);
}

GLuint Texture::getColorTexture() {
    return colorTexture;
}

GLuint Texture::getNormalMap() {
    return normalMap;
}

GLuint Texture::getSpecularTexture() {
    return specularTexture;
}

GLuint Texture::loadTexture(char* filename) {
    GLuint texture;
    std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
    unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
    glActiveTexture(GL_TEXTURE0);
    unsigned error = lodepng::decode(image, width, height, filename);
    glGenTextures(1,&texture); //Zainicjuj jeden uchwyt
    glBindTexture(GL_TEXTURE_2D, texture); //Uaktywnij uchwyt
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*) image.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return texture;
}

void Texture::loadColorTexture(char * filename) {
    colorTexture = loadTexture(filename);
}

void Texture::loadNormalMap(char * filename) {
    normalMap = loadTexture(filename);
}

void Texture::loadSpecularTexture(char * filename) {
    specularTexture = loadTexture(filename);
}