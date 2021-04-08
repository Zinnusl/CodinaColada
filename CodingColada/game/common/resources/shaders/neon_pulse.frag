#version 330 core

uniform vec4 color;
uniform vec2 screenresolution;
uniform float time;
uniform vec2 resolution;
uniform vec2 offset;


void main() 
{
    vec2 uv = offset + (gl_FragCoord.xy - 0.5 * resolution.xy) / resolution.y;  

    vec2 gv = uv * 50.0;
    gv = fract(gv) - 0.5;

    float t = time * 3.0;
    float s = (sin(t - length(uv * 2.0) * 5.0) * 0.4 + 0.5) * 0.6;
    float m = smoothstep(s, s - 0.05, length(gv)) + s*2.0;
    vec3 col = vec3(s, 0.0, 0.5) * m;

    gl_FragColor = vec4(col, 1.0);
    //gl_FragColor = vec4(gl_FragCoord.xy /  screenresolution.xy, 0, 1.0);
}