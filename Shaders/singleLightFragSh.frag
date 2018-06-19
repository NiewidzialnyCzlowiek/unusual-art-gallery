#version 330
out vec4 color;

in vec4 l; //Wektor do swiatla w przestrzeni oka
in vec4 n; //Wektor normalny w przestrzeni oka
in vec4 v; // do obserwatora w przestrzeni oka
in float lightIntensity;
in vec2 intUv;

uniform sampler2D colorTextureUnit;
uniform sampler2D specularTextureUnit;
uniform int useTextures;

void main() {
    vec4 normal = normalize(n);
    vec4 light = normalize(l);
    vec4 viewer = normalize(v);
    vec4 la=vec4(0.1,0.1,0.1,0); //Kolor swiatla otoczenia
    vec4 ld=vec4(1,1,1,1); //Kolor swiatla rozpraszanego
    vec4 ls=vec4(1,1,1,0); //Kolor swiatla odbijanego

    vec4 ambient = la;

    float diffuseStrength = 0.5;
    vec4 diffuse = max(dot(normal, light), 0.f) * ld;

    vec4 refl = reflect(-light, normal);
    vec4 specular = pow(max(dot(refl, viewer), 0.0f), 32) * ls;

    if(useTextures == 0) {
        color = vec4((ambient
            + diffuse
            ).xyz
            // + specular) 
            * lightIntensity
            , 1);
    } else {
        color = vec4((ambient
            + diffuse * texture(colorTextureUnit, intUv)
            // ).xyz
            + specular * texture(specularTextureUnit, intUv)).xyz 
            * lightIntensity
            , 1);
    }
}