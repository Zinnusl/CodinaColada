#version 330 core
layout (location = 0) in vec2 vertex;
uniform mat4 model;
uniform mat4 projection;
uniform mat4 camera; //view

void main()
{
	//Any changes here have to be reflected in the OpenGLRenderer: WorldToScreen/ScreenToWorld would break
	gl_Position =  projection * camera * model * vec4(vertex.xy, 0,  1.0);
};