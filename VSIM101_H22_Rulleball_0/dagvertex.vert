#version 330 core

layout(location = 0) in vec4 posAttr;
layout(location = 1) in vec4 colAttr;
out vec4 col;
uniform mat4 pmatrix;
uniform mat4 vmatrix;
uniform mat4 matrix;
uniform vec3 light_position;
//
// Beregner vha Phong shading
out vec3 vLightWeight;

// Disse kan vi vanligvis angi i C++ programmet
vec3 ambientColor = vec3(0.2, 0.2, 0.2);
vec3 diffuseColor = vec3(0.4, 0.4, 0.4);
vec3 specularColor = vec3(0.5, 0.5, 0.1);
const float shininess = 1.0;

void main() {
   //col = colAttr;
   //gl_Position = pmatrix * vmatrix * matrix * posAttr;
    vec4 vertexPositionEye4 = matrix * posAttr;
    vec3 vertexPositionEye3 = vertexPositionEye4.xyz;
    vec3 vectorToLightSource = normalize(light_position-vertexPositionEye3);
   // vec3 normalEye = normailze(uNMatrix*aVertexNormal);
    vec4 temp = vmatrix*matrix *colAttr;
    vec3 normalEye = normalize(temp.xyz);
    float diffuseLightWeight = max (dot(normalEye, vectorToLightSource), 0.0);
    vec3 reflectionVector = normalize(reflect(-vectorToLightSource, normalEye));
    vec3 viewVectorEye = - normalize(vertexPositionEye3);
    float rdotv = max(dot(reflectionVector, viewVectorEye), 0.0);
    float specularLightWeight = pow(rdotv, shininess);
    vLightWeight = ambientColor +
            diffuseColor*diffuseLightWeight +// +
           specularColor*specularLightWeight;

    gl_Position = pmatrix*vmatrix*matrix * posAttr;
    col = colAttr;//*vec4(1.0, 0.5, 0.2, 1.0);//
    //vTextureCoordinates = aTextureCoordinates;
}
