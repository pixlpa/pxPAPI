#ifdef GL_ES
precision highp float;
#endif

vec2 random2(vec2 st){
    st = vec2( dot(st,vec2(127.1,311.7)),
              dot(st,vec2(269.5,183.3)) );
    return -1.0 + 2.0*fract(sin(st)*43758.5453123);
}

float noise(vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);
    
    vec2 u = smoothstep(0.,1.,f);
    
    return mix( mix( dot( random2(i + vec2(0.0,0.0) ), f - vec2(0.0,0.0) ),
                    dot( random2(i + vec2(1.0,0.0) ), f - vec2(1.0,0.0) ), u.x),
               mix( dot( random2(i + vec2(0.0,1.0) ), f - vec2(0.0,1.0) ),
                   dot( random2(i + vec2(1.0,1.0) ), f - vec2(1.0,1.0) ), u.x), u.y);
}

uniform sampler2D tex0;
const vec4 LC = vec4(0.333,0.333,0.333,0.);
uniform vec2 size;
uniform float time;
const float pi=3.1415926;

varying vec2 texc;

void main(void)
{
    vec2 texcord = texc;
    vec2 ntexc = texc*vec2(size.x/size.y,1.);
    float a = smoothstep(-0.2,0.5,noise(ntexc*40.+vec2(0.,-time*0.4)))*0.5+0.5;
    vec2 c = vec2(noise(ntexc*5.+vec2(time*0.1,0.)),noise(ntexc*5.+vec2(5.)+vec2(0.,time*0.2)))*0.5+vec2(0.5);
    gl_FragColor = vec4(a,c,1.);
}

