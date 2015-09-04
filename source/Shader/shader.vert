#version 420

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

in vec4 vertex;

void main(){
	gl_Position = modelViewMatrix * projectionMatrix * vertex;
}