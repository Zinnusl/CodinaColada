#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec4 spriteColor;

void main()
{    
   // color = vec4(1,0,0,1);
    color = vec4(spriteColor) * texture(image, TexCoords);
}  