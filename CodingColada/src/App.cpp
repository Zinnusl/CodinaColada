#include "App.h"

#include <thread>
#include <chrono>

#include "IRenderer.h"
#include "GameObject.h"
#include "ShapeComponent.h"
#include "RigidbodyComponent.h"
#include "opengl/OpenGLRectangleShape.h"
#include "opengl/OpenGLRenderer.h"
#include "Color.h"


class Ball : public GameObject
{
	Vector2 velocity_;
public:
	Ball(Vector2 position, Vector2 velocity = { 0.6,0.3 })
		: GameObject(position), velocity_(velocity)
	{
	}

	void OnUpdate(float deltaTime) override
	{
		static float runtime = 0;
		runtime += deltaTime;
		Vector2 newPos = position_ +  velocity_ * deltaTime * 0.001;;

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
		
		if (newPos.GetX() < 0 || newPos.GetX() > 1600)
		{
			newPos = Vector2(800, 450);
			velocity_ = Vector2(abs(1 * sinf(runtime)) +0.3, 1* sinf(runtime));
		}
		position_ = newPos;
	}

	void OnCollision(RigidbodyComponent& other)
	{
		velocity_.SetX(-velocity_.GetX());
	}
};


class Paddle : public GameObject
{
	float speed = 0.4;
public:
	Paddle()
	{
	}
	
	Paddle(Vector2 position)
		: GameObject(position)
	{
	}
	
	void OnUpdate(float deltaTime) override
	{
		#define 	GLFW_KEY_DOWN   264
		#define 	GLFW_KEY_UP   265
		const int maxMove = 700;
		if (engine_->GetInput().GetKey(GLFW_KEY_DOWN))
		{
			float yPos = position_.GetY();
			if (position_.GetY() > 0)
			{
				float newPos = position_.GetY() - speed * deltaTime * 0.001;
				if (newPos < 0)
				{
					newPos = 0;
				}
				position_.SetY(newPos);
			}
		}
		if (engine_->GetInput().GetKey(GLFW_KEY_UP))
		{
			float yPos = position_.GetY();
			if (position_.GetY() < maxMove)
			{
				float newPos = position_.GetY() + speed * deltaTime * 0.001;
				if (newPos > maxMove)
				{
					newPos = maxMove;
				}
				position_.SetY(newPos);
			}
		}
	}
};

GameManager::GameManager()
{

}

void GameManager::OnUpdate(float deltaTime)
{
	int GLFW_KEY_ESCAPE = 256;
	if (engine_->GetInput().GetKeyDown(GLFW_KEY_ESCAPE))
	{
		if (components_.size() > 0)
		{
			RemoveComponent(*components_[0]);
		}
		else
		{
			engine_->StopGame();
		}
	}
}

App::App(std::ostream& logger, std::unique_ptr<Engine> engine)
	: logger_(logger), engine_(std::move(engine))
{
}

void App::run()
{
	const Vector2 windowSize = { 1600, 900 };
	void* window = engine_->GetRenderer().CreateWindow(windowSize.GetX(), windowSize.GetY());
	engine_->GetInput().RegisterWindow(window);
	//logger_ << "Ich bin eine App? Dachte da an so ein Schachspiel.\n"; // <-- mich auskommentieren um den test zu testen(falls man sowas tut?)

	//auto gameManager = std::make_unique<GameManager>(engine_);
	auto gameManager = std::make_unique<GameManager>();

	/*
	auto shape = std::make_unique<OpenGLRectangleShape>(Vector2(200, 300), Vector2(200, 70), Color(1, 0, 0, 1));
	auto shapeComponent = std::make_unique<ShapeComponent>(std::move(shape));
	gameManager->AddComponent(std::move(shapeComponent));
	*/

	//Vector2(windowSize.GetX() - paddleSize.GetX() * 2 - paddleSize.GetX(), windowSize.GetY() / 2 - paddleSize.GetY() / 2)

	Vector2 paddleSize = { 20, 200 };
	auto paddle1 = std::make_unique<Paddle>(Vector2(40, 400));
	paddle1->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(paddleSize, Color(0, 0, 1, 1))));
	paddle1->AddComponent(std::make_unique<RigidbodyComponent>(paddleSize));

	auto paddle2 = std::make_unique<Paddle>(Vector2(1540, 400));
	paddle2->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(paddleSize, Color(1, 0, 0, 1))));
	paddle2->AddComponent(std::make_unique<RigidbodyComponent>(paddleSize));

	auto ball = std::make_unique<Ball>(Vector2(800, 450));
	ball->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(Vector2(30, 20), Color(0, 1, 0, 1))));
	ball->AddComponent(std::make_unique<RigidbodyComponent>(Vector2(10)));

	engine_->AddGameObject(std::move(gameManager));
	engine_->AddGameObject(std::move(paddle1));
	engine_->AddGameObject(std::move(paddle2));
	engine_->AddGameObject(std::move(ball));

	engine_->StartGame();
}