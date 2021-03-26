#version 330 core

uniform vec4 color;
uniform vec2 screenresolution;
uniform float time;



void main() 
{
	int cellPixelSize = 64;
	if (mod(gl_FragCoord.x, cellPixelSize) < 1.0 || mod(gl_FragCoord.y, cellPixelSize) < 1.0 )
	{
		discard;
	}

	gl_FragColor = vec4(0.2, 0.8,0.1,0.1); 

	//int cells = 16;

	//vec2 normalized = vec2(gl_FragCoord.xy/screenresolution);

	//gl_FragColor = vec4(0.33,0.33,0.33,0.1);
	//if (mod(gl_FragCoord.x, screenresolution.y / cells) < 1.0 || mod(gl_FragCoord.y, screenresolution.y / cells) < 1.0)
	//{
	//	gl_FragColor = vec4(0.33,1,0.33,0.1); 
	//}
	
}