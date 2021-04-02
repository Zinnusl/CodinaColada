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
		discard;
	}

	gl_FragColor = vec4(0.2, 0.8,0.1,0.1); 

}