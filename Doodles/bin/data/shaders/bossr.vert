varying vec2 texc;

void main(void){
    gl_TexCoord[0] = gl_MultiTexCoord0;
    texc = gl_MultiTexCoord0.xy;
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_FrontColor = vec4(1.);
}
