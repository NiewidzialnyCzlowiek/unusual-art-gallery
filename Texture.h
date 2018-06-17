#ifndef UNUSUALARTGALLERY_TEXTURE_H
#define UNUSUALARTGALLERY_TEXTURE_H

#include "Lodepng/lodepng.h"
#include "GL/glew.h"
#include<vector>

class Texture {
private:
    GLuint colorTexture;
    GLuint normalMap;
    GLuint specularTexture;
    GLuint loadTexture(char * filename);

public:
    Texture();
    
    ~Texture();

    GLuint getColorTexture();

    GLuint getNormalMap();

    GLuint getSpecularTexture();

    void loadColorTexture(char * filename);
    
    void loadNormalMap(char * filename);
    
    void loadSpecularTexture(char * filename);
};

#endif //UNUSUALARTGALLERY_TEXTURE_H