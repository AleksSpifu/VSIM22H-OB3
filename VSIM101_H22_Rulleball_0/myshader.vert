#version 410 core

layout(location = 0) in vec4 positionIn;
layout(location = 1) in vec4 colorIn;

out vec4 color;
uniform mat4 mMatrix;
uniform mat4 vMatrix;
uniform mat4 pMatrix;

void main() {
   color = colorIn;
   gl_Position = pMatrix * vMatrix * mMatrix * positionIn;
}
