#pragma once

#include "../GameObject.h"

namespace di = boost::di;

class Ball : public GameObject
{
	Vector2 velocity_;

public:
	typedef di::extension::ifactory<Ball, Vector2, Vector2> ifactory_t;

	Ball(IEngine& engine, Vector2 position, Vector2 velocity)
		: GameObject(engine, position), velocity_(velocity)
	{
	}

	void OnUpdate(float deltaTime) override
	{
		static float runtime = 0;
		runtime += deltaTime;
		Vector2 newPos = position_ + velocity_ * deltaTime;

		if (newPos.GetY() <= 0)
		{
			newPos.SetY(0);
			velocity_.SetY(-velocity_.GetY());
		}
		if (newPos.GetY() >= 900) //size nicht vergessen
		{
			newPos.SetY(900);
			velocity_.SetY(-velocity_.GetY());
		}

		/*if (newPos.GetX() < 0 || newPos.GetX() > 1600)
		{
			newPos = Vector2(800, 450);
			velocity_ = Vector2(abs(0.01 * sinf(runtime)) +0.03, 0.01* sinf(runtime)) * 8;
		}*/

		if (newPos.GetX() <= 0)
		{
			newPos.SetX(0);
			velocity_.SetX(-velocity_.GetX());
		}
		if (newPos.GetX() >= 1600) //size nicht vergessen
		{
			newPos.SetX(1600);
			velocity_.SetX(-velocity_.GetX());
		}
		position_ = newPos;
	}

	void OnCollision(RigidbodyComponent& other)
	{
		velocity_.SetX(-velocity_.GetX());
	}
};