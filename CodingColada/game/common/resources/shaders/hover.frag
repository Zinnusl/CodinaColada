#version 330 core

uniform vec4 color;
uniform vec2 screenresolution;
uniform float time;



void main() 
{
	gl_FragColor = vec4(color.xyz, min(sin(time*4), 0.8)); 
}