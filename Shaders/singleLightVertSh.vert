#version 330
in vec4 vertex;
in vec4 normal;
// in vec4 color;
in vec2 uv;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform vec3 playerPosition;
uniform float lightRange;
uniform vec3 lightPosition[4];

out vec4 l; //wektor do swiatla w przestrzeni oka
out vec4 n; //wektor normalny w przestrzeni oka
out vec4 v; // wektor do obserwatora w przestrzeni oka
out float lightIntensity;
out vec2 intUv;

void main() {
    vec3 lightPos;
    lightIntensity = 0;
    float dist = length(vec4(lightPosition[0],1) - M*vertex);
    float minDist = dist;
    if(minDist >= dist) {
        lightPos = lightPosition[0];
        minDist = dist;
        lightIntensity = 1-dist/lightRange;
    }

    dist = length(vec4(lightPosition[1],1) - M*vertex);
    if(minDist >= dist) {
        minDist = dist;
        lightPos = lightPosition[1];
        lightIntensity = 1-dist/lightRange;
    }
    
    dist = length(vec4(lightPosition[2],1) - M*vertex);
    if(minDist >= dist) {
        lightPos = lightPosition[2];
        minDist = dist;
        lightIntensity = 1-dist/lightRange;
    }

    dist = length(vec4(lightPosition[3],1) - M*vertex);
    if(minDist >= dist) {
        lightPos = lightPosition[3];
        minDist = dist;
        lightIntensity = 1-dist/lightRange;
    }

    vec4 lp=vec4(lightPos, 1);
    vec4 ppos=vec4(playerPosition, 1);
    l=normalize(V*lp-V*M*vertex);
    n=normalize(V*M*normal);
    v=normalize(V*ppos-V*M*vertex); 
    gl_Position = P * V * M * vertex;
    intUv = uv;
}