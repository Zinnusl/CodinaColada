#version 330 core

uniform vec4 color;
uniform vec2 screenresolution;
uniform vec2 resolution;
uniform vec2 offset;
uniform float time;


void main() 
{
   	vec2 uv = (gl_FragCoord.xy - offset) / resolution.xy;
    float s1 = 0.5+0.5*sin(time+uv.x*3.1415*(sin(time)+4.0));
    float s2 = 0.5+0.25*sin(time+uv.x*3.1415*(sin(time)*2.0+2.0));
    float r = pow(1.0-sqrt( abs(uv.y-s1)),1.5 );
    float g = pow(1.0-sqrt( abs(uv.y-s2)),1.5 );
    float b = 1.5*(r+g);


	gl_FragColor = vec4( r * uv.x, 0 ,b * uv.y,1 );

}