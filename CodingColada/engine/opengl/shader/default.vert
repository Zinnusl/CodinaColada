#version 330 core
layout (location = 0) in vec2 vertex;
uniform mat4 model;
uniform mat4 projection;
uniform mat4 camera;

void main()
{
   gl_Position =  camera * projection * model * vec4(vertex.xy, 0,  1.0);
};