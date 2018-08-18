#ifdef GL_ES
precision highp float;
#endif

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 textureMatrix;
uniform mat4 modelViewProjectionMatrix;

attribute vec4  position;
attribute vec2 texcoord;
attribute vec4 color;
attribute vec3 normal;

varying vec2 texc;

void main(void){
    texc = texcoord;
    gl_Position = modelViewProjectionMatrix * gl_Vertex;
}
