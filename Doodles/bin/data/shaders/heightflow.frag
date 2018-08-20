#ifdef GL_ES
precision highp float;
#endif

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform float power;
uniform float offset;
uniform float bright;
uniform float dark;
uniform float contrast;
uniform float warp;
uniform vec2 shift;
const vec4 LC = vec4(0.333,0.333,0.333,0.);
uniform float mixin;
uniform float aspect;
uniform vec2 size;
uniform float time;
const float pi=3.1415926;
const float samples = 8.;

varying vec2 texc;

void main(void)
{
    vec2 texcord = texc;
    vec2 ntexc = texc*vec2(size.x/size.y,1.);
    vec4 a = texture2D(tex0,texc);
    vec4 bnoise = texture2D(tex1,abs(0.5-fract(texc*0.2+vec2(time*0.0051,time*0.00053)))*2.);
    bnoise.r = smoothstep(0.35,0.85,bnoise.r);
    vec2 accumxy = vec2(0.,0.);
    vec2 asp = vec2(aspect,1.);
    
    //top left
    vec2 tca = vec2(-1.,-1.)/size;
    float tick = dot(texture2D(tex0, texcord+tca*offset),LC)-0.5;
    accumxy += tca*tick;
    //top center
    tca = vec2(0.,-1.)/size;
    tick = dot(texture2D(tex0, texcord+tca*offset),LC)-0.5;
    accumxy += tca*tick;
    //top right
    tca = vec2(1.,-1.)/size;
    tick = dot(texture2D(tex0, texcord+tca*offset),LC)-0.5;
    accumxy += tca*tick;
    //center left
    tca = vec2(-1.,0.)/size;
    tick = dot(texture2D(tex0, texcord+tca*offset),LC)-0.5;
    accumxy += tca*tick;
    //center right
    tca = vec2(1.,0.)/size;
    tick = dot(texture2D(tex0, texcord+tca*offset),LC)-0.5;
    accumxy += tca*tick;
    //bottom left
    tca = vec2(-1.,1.)/size;
    tick = dot(texture2D(tex0, texcord+tca*offset),LC)-0.5;
    accumxy += tca*tick;
    //bottom center
    tca = vec2(0.,1.)/size;
    tick = dot(texture2D(tex0, texcord+tca*offset),LC)-0.5;
    accumxy += tca*tick;
    //bottom right
    tca = vec2(1.,1.)/size;
    tick = dot(texture2D(tex0, texcord+tca*offset),LC)-0.5;
    accumxy += tca*tick;
    vec4 hit = mix(vec4(0.5,0.5,0.5,1.),texture2D(tex0, texcord+ accumxy*power + shift/size + (bnoise.gb*2.-vec2(1.))*warp/size) * vec4(vec3(bright),1.) - vec4(vec3(dark),0.),contrast);
    gl_FragColor = mix(mix(hit,vec4(vec3(bnoise.r),1.),mixin),a,0.02);
}

