#version 330 core

uniform vec4 color;
uniform vec2 screenresolution;
uniform float time;



void main() 
{
	gl_FragColor = vec4(0.1, 1, 0.2, min(sin(time*4), 0.8)); 
}