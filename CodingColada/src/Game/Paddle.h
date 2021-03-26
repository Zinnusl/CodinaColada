#pragma once

#include "../GameObject.h"
#include "../IEngine.h"

#define 	GLFW_KEY_DOWN   264
#define 	GLFW_KEY_UP   265

class Paddle : public GameObject
{
	float speed = 0.4;
public:
	Paddle(IEngine& engine, Vector2 position)
		: GameObject(engine, position)
	{
	}

	void OnUpdate(float deltaTime) override
	{
		const int maxMove = 700;
		if (engine_.GetInput().GetKey(GLFW_KEY_DOWN))
		{
			float yPos = position_.GetY();
			if (position_.GetY() > 0)
			{
				float newPos = position_.GetY() - speed * deltaTime;
				if (newPos < 0)
				{
					newPos = 0;
				}
				position_.SetY(newPos);
			}
		}
		if (engine_.GetInput().GetKey(GLFW_KEY_UP))
		{
			float yPos = position_.GetY();
			if (position_.GetY() < maxMove)
			{
				float newPos = position_.GetY() + speed * deltaTime;
				if (newPos > maxMove)
				{
					newPos = maxMove;
				}
				position_.SetY(newPos);
			}
		}
	}
};