#pragma once

#include "../RectangleShape.h"
#include "../Vector2.h"

class OpenGLRectangleShape : public RectangleShape
{
	unsigned int VAO;
public:
	OpenGLRectangleShape(Vector2 topLeft, Vector2 bottomRight);
	void Draw() override;
};