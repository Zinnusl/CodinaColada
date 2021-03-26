#pragma once

#include "../GameObject.h"

class Ball : public GameObject
{
	Vector2 velocity_;
public:
	Ball(IEngine& engine, Vector2 position, Vector2 velocity = { 0.0005,0.0005 })
		: GameObject(engine, position), velocity_(velocity)
	{
	}

	void OnUpdate(float deltaTime) override
	{
		previousPosition_ = currentPosition_;

		static float runtime = 0;
		runtime += deltaTime;
		Vector2 newPos = currentPosition_ + velocity_ * deltaTime;

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
		currentPosition_ = newPos;
	}

	void OnCollision(RigidbodyComponent& other)
	{
		velocity_.SetX(-velocity_.GetX());
	}
};