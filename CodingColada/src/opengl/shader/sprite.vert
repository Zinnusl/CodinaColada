#version 330 core
layout (location = 0) in vec2 vertex;
out vec2 TexCoords;
uniform mat4 model;
uniform mat4 projection;

void main()
{
   TexCoords = vertex.xy;
   //gl_Position =  projection * model * vec4(vertex.xy, 0,  1.0);
   gl_Position =  vec4(vertex.xy, 0,  1.0);
};