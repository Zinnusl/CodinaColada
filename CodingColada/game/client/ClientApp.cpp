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

	const Vector2 windowSize = { 1280, 720};
	//const Vector2 windowSize = { 1920, 1080 };
	//const Vector2 windowSize = { 2560, 1440 };
	
	void* window = engine->GetRenderer().CreateWindow(windowSize.GetX(), windowSize.GetY());
	engine->GetInput().RegisterWindow(window);

	renderer->LoadTexture("test_sprite_60x60", "..\\..\\..\\..\\CodingColada\\engine\\opengl\\texture\\test_sprite_60x60.png");
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
									"..\\..\\..\\..\\CodingColada\\engine\\opengl\\shader\\grid.frag", 
		[&](OpenGLShader& shader) {
		//Draw a grid with a cellsize of 10 game units
		int test = engine->GetRenderer().WorldToScreen(Vector2(10, 0)).GetX() - engine->GetRenderer().WorldToScreen(Vector2(0, 0)).GetX();
		printf("TEST %d\n", test);
		shader.SetInteger("cellPixelSize", test-2);
	});
	renderer->LoadShader("hover", "..\\..\\..\\..\\CodingColada\\engine\\opengl\\shader\\default.vert", "..\\..\\..\\..\\CodingColada\\game\\common\\resources\\shaders\\hover.frag");

	auto gameManager = std::make_unique<GameManager>();

	auto testCube = std::make_unique<GameObject>(Vector2{ 0, 0 });
	testCube->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(Vector2{ 10,10 }, Color(0, 0, 1, 1))));

	auto testCube1 = std::make_unique<GameObject>(Vector2{ 30,0 });
	testCube1->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(Vector2{ 10,10 }, Color(0, 0, 1, 1))));

	auto testCube2 = std::make_unique<GameObject>(Vector2{ 10,10 });
	testCube2->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(Vector2{ 20,20 }, Color(0, 0, 1, 1))));

	auto testSprite60x60 = std::make_unique<GameObject>(Vector2{ 30,30 });
	testSprite60x60->AddComponent(std::make_unique<SpriteComponent>(std::make_unique<OpenGLSprite>(glm::vec2(10, 10), OpenGLRenderer::shaders_["colada_shader_sprite"], OpenGLRenderer::textures_["test_sprite_60x60"])));

	auto testSprite60x60_2 = std::make_unique<GameObject>(Vector2{ 40,40 });
	testSprite60x60_2->AddComponent(std::make_unique<SpriteComponent>(std::make_unique<OpenGLSprite>(glm::vec2(10, 10), OpenGLRenderer::shaders_["colada_shader_sprite"], OpenGLRenderer::textures_["test_sprite_60x60"])));

	auto cameraManager = std::make_unique<CameraManager>();

	//auto build_grid = std::make_unique<Grid>(8, 8, 64, Vector2{ 100,100 });
	//build_grid->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(Vector2{ 8*64, 8*64 }, Color(1, 0, 0, 0.1))));

	auto engine_debug_grid = std::make_unique<GameObject>(Vector2(-1000000, -1000000));
	engine_debug_grid->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(Vector2{2000000, 2000000}, Color(0, 1, 0, 0.08), &OpenGLRenderer::shaders_["grid"])));

	Vector2 paddleSize = { 20, 200 };
	auto paddle1 = std::make_unique<Paddle>(Vector2(40, 400));
	paddle1->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(paddleSize, Color(0, 0, 1, 1))));
	paddle1->AddComponent(std::make_unique<RigidbodyComponent>(paddleSize));

	auto paddle2 = std::make_unique<Paddle>(Vector2(1540, 400));
	paddle2->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(paddleSize, Color(1, 0, 0, 1))));
	paddle2->AddComponent(std::make_unique<RigidbodyComponent>(paddleSize));

	auto ball = std::make_unique<Ball>(Vector2(800, 450));
	//ball->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(Vector2(20), Color(0, 1, 0, 1))));
	//ball->AddComponent(std::make_unique<SpriteComponent>(std::make_unique<OpenGLSprite>(glm::vec2(64, 64), OpenGLRenderer::shaders_["colada_shader_sprite"], OpenGLRenderer::textures_["watermelon"])));
	ball->AddComponent(std::make_unique<RigidbodyComponent>(Vector2(64)));

	auto ball2 = std::make_unique<Ball>(Vector2(1000, 450), Vector2(0, 0));
	auto ball3 = std::make_unique<Ball>(Vector2(2000, 450), Vector2(0, 0));
	auto ball4 = std::make_unique<Ball>(Vector2(3000, 450), Vector2(0, 0));
	auto ball5 = std::make_unique<Ball>(Vector2(4000, 450), Vector2(0, 0));

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
	ball2->AddComponent(std::make_unique<AnimatedSpriteComponent>(melonAnimation, 100000.0f));
	ball3->AddComponent(std::make_unique<AnimatedSpriteComponent>(melonAnimation, 100000.0f));
	ball4->AddComponent(std::make_unique<AnimatedSpriteComponent>(melonAnimation, 100000.0f));
	ball5->AddComponent(std::make_unique<AnimatedSpriteComponent>(melonAnimation, 100000.0f));


	engine->AddGameObject(std::move(engine_debug_grid));
	engine->AddGameObject(std::move(gameManager));
	engine->AddGameObject(std::move(cameraManager));

	//engine->AddGameObject(std::move(build_grid));
	engine->AddGameObject(std::move(paddle1));
	engine->AddGameObject(std::move(paddle2));
	engine->AddGameObject(std::move(ball));

	engine->AddGameObject(std::move(testCube));
	engine->AddGameObject(std::move(testCube1));
	engine->AddGameObject(std::move(testCube2));
	
	//engine->AddGameObject(std::move(testSprite60x60));
	//engine->AddGameObject(std::move(testSprite60x60_2));

	
	engine->AddGameObject(std::move(ball2));
	engine->AddGameObject(std::move(ball3));
	engine->AddGameObject(std::move(ball4));
	engine->AddGameObject(std::move(ball5));

	engine->StartGame();

	return 0;
}