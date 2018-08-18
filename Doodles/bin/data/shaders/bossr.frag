

uniform sampler2DRect tex0;
uniform float hscale;
uniform float nscale;
uniform vec2 offset;
uniform vec3 lightpos;
uniform float dthresh;
uniform float dfade;
uniform vec2 size;
uniform float aspect;
uniform float brightness;
varying vec2 texc;

void main( void ){
    vec2 texcord = texc;
    vec2 offs = texcord+offset*vec2(1.,-1.);
    float map0 = texture2DRect(tex0,texcord).r*hscale;
    float map1 = texture2DRect(tex0,vec2(offs.x,texcord.y)).r*hscale-map0;
    float map2 = texture2DRect(tex0,vec2(texcord.x,offs.y)).r*hscale-map0;
    vec3 shape = normalize(cross(vec3(1.,0.,map1),vec3(0.,1.,map2)));
    vec3 light = normalize(lightpos-vec3((texcord*vec2(2.)-vec2(1.)),(map0/hscale)*-nscale));
    float greyval = clamp(dot(light,shape),0.,1.);
    vec4 ic = texture2DRect(tex0,texcord);
    vec4 fc = mix(vec4(greyval)*brightness,ic,smoothstep(dthresh-dfade,dthresh+dfade,greyval));
    //gl_FragColor = vec4(fc.rgb,1.);
    gl_FragColor = vec4(fc.rgb,1.);
}
