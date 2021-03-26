#pragma once

#include "../RectangleShape.h"
#include "../Vector2.h"

class Shader;
class Engine;
class OpenGLRectangleShape : public RectangleShape
{
	//TODO shader kommt hier shape
	unsigned int VAO;
public:
	OpenGLRectangleShape(Vector2 size, Color color);
	void Draw(Engine& engine, GameObject& gameobject, float subframe) override;
};