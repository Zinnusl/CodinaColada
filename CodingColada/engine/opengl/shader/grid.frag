#version 330 core

uniform vec4 color;
uniform vec2 screenresolution;
uniform float time;
uniform float cellPixelSizeX;
uniform float cellPixelSizeY;
uniform vec2 pxOffset;

void main() 
{
   	if (mod(pxOffset.x+ gl_FragCoord.x +1.f, cellPixelSizeX) <= 2.0 || mod(pxOffset.y +gl_FragCoord.y +1.f, cellPixelSizeY) <= 2.0)
	{
		gl_FragColor = color;
	}
}