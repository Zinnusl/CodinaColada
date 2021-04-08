#version 330 core

uniform vec4 color;
uniform vec2 screenresolution;
uniform float time;
uniform float cellPixelSizeX;
uniform float cellPixelSizeY;
uniform vec2 pxOffset;

void main() 
{
	gl_FragColor = color;
}