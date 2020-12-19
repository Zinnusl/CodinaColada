#include "OpenGLRectangleShape.h"

OpenGLRectangleShape::OpenGLRectangleShape(Vector2 topLeft, Vector2 bottomRight)
	: RectangleShape(topLeft, bottomRight)
{

}

void OpenGLRectangleShape::Draw()
{
	printf("OpenGLRectangleShape\n");
}