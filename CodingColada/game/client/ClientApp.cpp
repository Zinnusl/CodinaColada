#include <thread>
#include <chrono>
#include "../../engine/Engine.h"
#include "../../engine/IRenderer.h"
#include "../../engine/GameObject.h"
#include "../../engine/ShapeComponent.h"
#include "../../engine/SpriteComponent.h"
#include "../../engine/AnimatedSpriteComponent.h"
#include "../../engine/RigidbodyComponent.h"
#include "../../engine/opengl/OpenGLRectangleShape.h"
#include "../../engine/opengl/OpenGLRenderer.h"
#include "../../engine/opengl/OpenGLInput.h"
#include "../../engine/opengl/OpenGLSprite.h"
#include "../../engine/Color.h"
#include "imgui.h"

#include "../common/Ball.h"
#include "../common/Paddle.h"
#include "../common/GameManager.h"
#include "../common/CameraManager.h"
#include "../common/Grid.h"
#include "../common/HoverTile.h"





int main()
{
	std::shared_ptr<OpenGLRenderer> renderer = std::make_shared<OpenGLRenderer>();
	std::unique_ptr<OpenGLInput> input = std::make_unique<OpenGLInput>();
	std::unique_ptr<Engine> engine = std::make_unique<Engine>(renderer, std::move(input));

	const Vector2 windowSize = { 2560, 1440 };
	void* window = engine->GetRenderer().CreateWindow(windowSize.GetX(), windowSize.GetY());
	engine->GetInput().RegisterWindow(window);

	renderer->LoadTexture("stone", "..\\..\\..\\..\\CodingColada\\game\\common\\resources\\textures\\stone.png");
	renderer->LoadTexture("watermelon", "..\\..\\..\\..\\CodingColada\\game\\common\\resources\\textures\\melon1.png");
	renderer->LoadTexture("watermelon2", "..\\..\\..\\..\\CodingColada\\game\\common\\resources\\textures\\melon2.png");
	renderer->LoadTexture("watermelon3", "..\\..\\..\\..\\CodingColada\\game\\common\\resources\\textures\\melon3.png");
	renderer->LoadTexture("watermelon4", "..\\..\\..\\..\\CodingColada\\game\\common\\resources\\textures\\melon4.png");
	renderer->LoadTexture("watermelon5", "..\\..\\..\\..\\CodingColada\\game\\common\\resources\\textures\\melon5.png");
	renderer->LoadTexture("watermelon6", "..\\..\\..\\..\\CodingColada\\game\\common\\resources\\textures\\melon6.png");
	renderer->LoadTexture("watermelon7", "..\\..\\..\\..\\CodingColada\\game\\common\\resources\\textures\\melon7.png");
	renderer->LoadTexture("watermelon8", "..\\..\\..\\..\\CodingColada\\game\\common\\resources\\textures\\melon8.png");
	renderer->LoadTexture("hovertile", "..\\..\\..\\..\\CodingColada\\game\\common\\resources\\textures\\Tile_Hover.png");
	renderer->LoadTexture("tower_canon", "..\\..\\..\\..\\CodingColada\\game\\common\\resources\\textures\\canon_tower.png");

	renderer->LoadShader("grid",	"..\\..\\..\\..\\CodingColada\\engine\\opengl\\shader\\default.vert",
									"..\\..\\..\\..\\CodingColada\\game\\common\\resources\\shaders\\grid.frag", 
		[](OpenGLShader& shader) {
			shader.SetInteger("cellPixelSize", 64);
	});
	renderer->LoadShader("hover", "..\\..\\..\\..\\CodingColada\\engine\\opengl\\shader\\default.vert", "..\\..\\..\\..\\CodingColada\\game\\common\\resources\\shaders\\hover.frag");

	auto gameManager = std::make_unique<GameManager>();
	auto cameraManager = std::make_unique<CameraManager>();

	auto grid = std::make_unique<Grid>(32, 32, 64);
	grid->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(Vector2{ 32*64, 32 * 64 }, Color(0, 0, 1, 0.1), &OpenGLRenderer::shaders_["grid"])));

	Vector2 paddleSize = { 20, 200 };
	auto paddle1 = std::make_unique<Paddle>(Vector2(40, 400));
	paddle1->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(paddleSize, Color(0, 0, 1, 1))));
	paddle1->AddComponent(std::make_unique<RigidbodyComponent>(paddleSize));

	auto paddle2 = std::make_unique<Paddle>(Vector2(windowSize.GetX() - 60, 400));
	paddle2->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(paddleSize, Color(1, 0, 0, 1))));
	paddle2->AddComponent(std::make_unique<RigidbodyComponent>(paddleSize));

	auto ball = std::make_unique<Ball>(Vector2(800, 450));
	//ball->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(Vector2(20), Color(0, 1, 0, 1))));
	//ball->AddComponent(std::make_unique<SpriteComponent>(std::make_unique<OpenGLSprite>(glm::vec2(64, 64), OpenGLRenderer::shaders_["colada_shader_sprite"], OpenGLRenderer::textures_["watermelon"])));
	ball->AddComponent(std::make_unique<RigidbodyComponent>(Vector2(64)));

	std::vector<std::shared_ptr<ISprite>> melonAnimation;
	for (int i = 0; i < 10; i++) {
		melonAnimation.push_back(std::make_unique<OpenGLSprite>(glm::vec2(64, 64), OpenGLRenderer::shaders_["colada_shader_sprite"], OpenGLRenderer::textures_["watermelon"]));
	}
	melonAnimation.push_back(std::make_unique<OpenGLSprite>(glm::vec2(64, 64), OpenGLRenderer::shaders_["colada_shader_sprite"], OpenGLRenderer::textures_["watermelon2"]));
	melonAnimation.push_back(std::make_unique<OpenGLSprite>(glm::vec2(64, 64), OpenGLRenderer::shaders_["colada_shader_sprite"], OpenGLRenderer::textures_["watermelon3"]));
	melonAnimation.push_back(std::make_unique<OpenGLSprite>(glm::vec2(64, 64), OpenGLRenderer::shaders_["colada_shader_sprite"], OpenGLRenderer::textures_["watermelon4"]));
	melonAnimation.push_back(std::make_unique<OpenGLSprite>(glm::vec2(64, 64), OpenGLRenderer::shaders_["colada_shader_sprite"], OpenGLRenderer::textures_["watermelon5"]));
	melonAnimation.push_back(std::make_unique<OpenGLSprite>(glm::vec2(64, 64), OpenGLRenderer::shaders_["colada_shader_sprite"], OpenGLRenderer::textures_["watermelon6"]));
	melonAnimation.push_back(std::make_unique<OpenGLSprite>(glm::vec2(64, 64), OpenGLRenderer::shaders_["colada_shader_sprite"], OpenGLRenderer::textures_["watermelon7"]));
	melonAnimation.push_back(std::make_unique<OpenGLSprite>(glm::vec2(64, 64), OpenGLRenderer::shaders_["colada_shader_sprite"], OpenGLRenderer::textures_["watermelon8"]));
	
	ball->AddComponent(std::make_unique<AnimatedSpriteComponent>(melonAnimation, 100000.0f));


	engine->AddGameObject(std::move(gameManager));
	engine->AddGameObject(std::move(cameraManager));
	engine->AddGameObject(std::move(grid));
	engine->AddGameObject(std::move(paddle1));
	engine->AddGameObject(std::move(paddle2));
	engine->AddGameObject(std::move(ball));

	engine->StartGame();

	return 0;
}