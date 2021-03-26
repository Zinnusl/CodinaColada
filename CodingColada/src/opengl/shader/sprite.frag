#version 330 core
in vec2 TexCoords;

uniform sampler2D image;
uniform vec4 spriteColor;

void main()
{    
    gl_FragColor = vec4(spriteColor) * texture(image, TexCoords);
}  