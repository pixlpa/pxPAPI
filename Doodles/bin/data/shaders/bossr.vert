#ifdef GL_ES
precision highp float;

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
#else
varying vec2 texc;

void main(void){
    gl_TexCoord[0] = gl_MultiTexCoord0;
    texc = gl_MultiTexCoord0.xy;
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_FrontColor = vec4(1.);
}
#endif

