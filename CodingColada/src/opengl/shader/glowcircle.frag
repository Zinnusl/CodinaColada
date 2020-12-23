#version 330 core
uniform float iTime;				// shader playback time (in seconds)
uniform vec2  iResolution;          // viewport resolution (in pixels)
uniform vec2  iMouse;  

void main()
{
	float radius = 2;
	vec2 p = (2.*gl_FragCoord.xy-iResolution.xy) / iResolution.y; 
	gl_FragColor = vec4( radius / (0. * abs(2.*length(p)-1.) ) );
}