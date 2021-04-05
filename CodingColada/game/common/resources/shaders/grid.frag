#version 330 core

uniform vec4 color;
uniform vec2 screenresolution;
uniform float time;
uniform int cellPixelSize;
uniform float zoom;
uniform mat4 projection;
uniform mat4 camera;

void main() 
{
	vec4 cellSize2 = projection* camera* vec4(cellPixelSize, 0, 0, 1);
	gl_FragColor = cellSize2;
		//if (mod(gl_FragCoord.x, cellPixelSize * zoom) < 1.0 || mod(gl_FragCoord.y, cellPixelSize * zoom) < 1.0)
	//if (mod(gl_FragCoord.x, cellSize2.x) < 1.0 || mod(gl_FragCoord.y, cellSize2.x) < 1.0)
	{
	//	gl_FragColor = color;
	}
	//else 
	{
	//	discard;
	}
}