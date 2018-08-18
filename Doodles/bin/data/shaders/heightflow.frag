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
const float samples = 12.;

varying vec2 texc;

void main(void)
{
    vec2 texcord = texc;
    vec2 ntexc = texc*vec2(size.x/size.y,1.);
    vec4 a = texture2D(tex0,texc);
    vec4 b = vec4(smoothstep(-0.2,0.5,vec3(noise(ntexc*10.+vec2(0.,-time*0.4)))),1.);
    vec2 c = vec2(noise(ntexc*2.+vec2(time*0.1,0.)),noise(ntexc*2.+vec2(5.)+vec2(0.,time*0.2)));
    b = vec4(vec3(dot(b,LC)),1.);
    vec2 accumxy = vec2(0.,0.);
    vec2 asp = vec2(aspect,1.);
    for(float i=0.; i<samples; i++){
        float ti = i+time;
        vec2 tca = vec2(sin(ti*pi*2./samples),cos(ti*pi*2./samples))/size;
        float tick = dot(texture2D(tex0, texcord+tca*offset),LC)-0.5;
        tick += dot(texture2D(tex0, texcord+tca*offset*2.),LC)-0.5;
        accumxy += tca * tick/2.;
    }
    vec4 hit = mix(vec4(0.5,0.5,0.5,1.),texture2D(tex0, texcord+ accumxy*power + shift/size + c*warp/size) * vec4(vec3(bright),1.) - vec4(vec3(dark),0.),contrast);
    gl_FragColor = mix(mix(hit,b,mixin),a,0.02);
}

