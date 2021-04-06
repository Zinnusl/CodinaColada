#pragma once

#include "../RectangleShape.h"
#include "../Vector2.h"


class Engine;
class OpenGLShader;
class OpenGLRectangleShape : public RectangleShape
{
	static unsigned int VAO;

	std::shared_ptr<OpenGLShader> customShader_;

public:
	OpenGLRectangleShape(Vector2 size, Color color);
	OpenGLRectangleShape(Vector2 size, Color color, OpenGLShader* customShader);
	void Draw(Engine& engine, GameObject& gameobject, float subframe, float deltaTime) override;

	static void InitRenderData();
};