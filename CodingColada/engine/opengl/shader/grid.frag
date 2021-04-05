#version 330 core

uniform vec4 color;
uniform vec2 screenresolution;
uniform float time;
uniform int cellPixelSize;
uniform float zoom;


void main() 
{
	if (mod(gl_FragCoord.x, cellPixelSize * zoom) < 1.0 || mod(gl_FragCoord.y, cellPixelSize * zoom) < 1.0)
	{
		gl_FragColor = color;
	}
	else 
	{
		discard;
	}
}