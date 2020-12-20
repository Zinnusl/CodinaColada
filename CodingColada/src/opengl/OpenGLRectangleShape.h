#pragma once

#include "../RectangleShape.h"
#include "../Vector2.h"

class Shader;
class OpenGLRectangleShape : public RectangleShape
{
	//TODO shader kommt hier shape
	unsigned int VAO;
public:
	OpenGLRectangleShape(Vector2 topLeft, Vector2 bottomRight);
	void Draw() override;
};