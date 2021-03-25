#version 330 core

uniform vec4 color;
uniform vec2 screenresolution;
uniform float time;


void main() 
{
	vec2 cellsize = vec2(32,32);

	vec2 normalized = vec2(gl_FragCoord.xy/screenresolution);
	
	gl_FragColor = vec4(normalized.x, 0, normalized.y, color.w);

	//vec2 center =  vec2(0.5,0.5);
	//vec2 delta = normalized - center;
	//float distance = sqrt(dot(delta, delta));
	//if (distance > mod(sin(time), 0.5) && distance < mod(sin(time), 0.5) + 0.1)
	//{
	//	gl_FragColor = vec4(sin(time), cos(time),0,color.w);
	//}
	//else
	//{
	//	gl_FragColor = vec4(tan(time), cos(time), sin(time),color.w);
	//}
}