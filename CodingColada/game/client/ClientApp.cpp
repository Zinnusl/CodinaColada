#include <thread>
#include <chrono>
#include "../../engine/Engine.h"
#include "../../engine/IRenderer.h"
#include "../../engine/audio/FMODSoundManager.h"
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
	std::unique_ptr<FMODSoundManager> audio = std::make_unique<FMODSoundManager>();
	std::unique_ptr<Engine> engine = std::make_unique<Engine>(renderer, std::move(input), std::move(audio));


	//const Vector2 windowSize = { 400, 720 };
	//const Vector2 windowSize = { 1280, 720};
	//const Vector2 windowSize = { 1600, 1000};
	const Vector2 windowSize = { 1920, 1080 };
	//const Vector2 windowSize = { 2000, 1000 };
	//const Vector2 windowSize = { 2560, 1440 };

	const Vector2 engineUnits = { 2560, 1440 };
	
	void* window = engine->GetRenderer().CreateWindow(windowSize.GetX(), windowSize.GetY(), engineUnits.GetX(), engineUnits.GetY(), false);
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
		//Draw a grid with a cellsize of 10 EU
		shader.SetFloat("cellPixelSizeX", engine->GetRenderer().WorldToScreen(Vector2(10, 0)).GetX() - engine->GetRenderer().WorldToScreen(Vector2(0, 0)).GetX());
		shader.SetFloat("cellPixelSizeY", engine->GetRenderer().WorldToScreen(Vector2(0, 10)).GetY() - engine->GetRenderer().WorldToScreen(Vector2(0, 0)).GetY());

		//Doesnt quite work how I want it do.. Should move the grid.. but makes me dizzy..
		//shader.SetVector2f("pxOffset", engine->GetRenderer().GetCameraPosition().GetX(), engine->GetRenderer().GetCameraPosition().GetY());
	});
	renderer->LoadShader("build_grid", "..\\..\\..\\..\\CodingColada\\engine\\opengl\\shader\\default.vert",
		"..\\..\\..\\..\\CodingColada\\game\\common\\resources\\shaders\\build_grid.frag",
		[&](OpenGLShader& shader) {
		//Draw a grid with a cellsize of 10 EU
		shader.SetFloat("cellPixelSizeX", engine->GetRenderer().WorldToScreen(Vector2(10, 0)).GetX() - engine->GetRenderer().WorldToScreen(Vector2(0, 0)).GetX());
		shader.SetFloat("cellPixelSizeY", engine->GetRenderer().WorldToScreen(Vector2(0, 10)).GetY() - engine->GetRenderer().WorldToScreen(Vector2(0, 0)).GetY());

		shader.SetVector2f("pxOffset", engine->GetRenderer().GetCameraPosition().GetX(), engine->GetRenderer().GetCameraPosition().GetY());
	});
	renderer->LoadShader("hover", "..\\..\\..\\..\\CodingColada\\engine\\opengl\\shader\\default.vert", "..\\..\\..\\..\\CodingColada\\game\\common\\resources\\shaders\\hover.frag");
	renderer->LoadShader("ignore_camera_rectangle", "..\\..\\..\\..\\CodingColada\\engine\\opengl\\shader\\ignore_camera.vert", "..\\..\\..\\..\\CodingColada\\engine\\opengl\\shader\\default.frag");
	renderer->LoadShader("neon", "..\\..\\..\\..\\CodingColada\\engine\\opengl\\shader\\default.vert", "..\\..\\..\\..\\CodingColada\\game\\common\\resources\\shaders\\neon.frag");
	renderer->LoadShader("neon_pulse", "..\\..\\..\\..\\CodingColada\\engine\\opengl\\shader\\default.vert", "..\\..\\..\\..\\CodingColada\\game\\common\\resources\\shaders\\neon_pulse.frag");

	auto gameManager = std::make_unique<GameManager>();

	auto yAxis = std::make_unique<GameObject>(Vector2{ -1, -1000000 });
	yAxis->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(Vector2{ 2,2000000 }, Color(0, 1, 1, 0.2))));
	auto xAxis = std::make_unique<GameObject>(Vector2{ -1000000, -1 });
	xAxis->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(Vector2{ 2000000, 2}, Color(0, 1, 1, 0.2))));

	auto testCube = std::make_unique<GameObject>(Vector2{ 0, 0 });
	testCube->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(Vector2{ 10,10 }, Color(0, 0, 1, 1))));

	auto testCube1 = std::make_unique<GameObject>(Vector2{ 30,0 });
	testCube1->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(Vector2{ 10,10 }, Color(0, 0, 1, 1))));

	auto testCube2 = std::make_unique<GameObject>(Vector2{ 10,10 });
	testCube2->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(Vector2{ 20,20 }, Color(0, 0, 1, 1))));

	auto testSprite60x60 = std::make_unique<GameObject>(Vector2{ 0,0 });
	testSprite60x60->AddComponent(std::make_unique<SpriteComponent>(std::make_unique<OpenGLSprite>(glm::vec2(10, 10), OpenGLRenderer::shaders_["colada_shader_sprite"], OpenGLRenderer::textures_["test_sprite_60x60"])));

	auto testSprite60x60_2 = std::make_unique<GameObject>(Vector2{ 10,10 });
	testSprite60x60_2->AddComponent(std::make_unique<SpriteComponent>(std::make_unique<OpenGLSprite>(glm::vec2(10, 10), OpenGLRenderer::shaders_["colada_shader_sprite"], OpenGLRenderer::textures_["test_sprite_60x60"])));

	auto cameraManager = std::make_unique<CameraManager>();

	auto engine_debug_grid = std::make_unique<GameObject>(Vector2(-1000000, -1000000));
	engine_debug_grid->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(Vector2{ 2000000, 2000000 }, Color(0, 1, 0, 0.08), &OpenGLRenderer::shaders_["grid"])));


	auto background = std::make_unique<GameObject>(Vector2(0));
	background->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(Vector2{ engineUnits.GetX(), engineUnits.GetY() }, Color(0, 1, 0, 0.08), &OpenGLRenderer::shaders_["neon_pulse"])));

	int32_t x = 16;
	int32_t y = 16;
	int32_t cellSize = 64;

	auto build_grid1 = std::make_unique<Grid>(x, y, cellSize, Vector2{ 128, 128 });
	build_grid1->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(Vector2{ (float)x* cellSize, (float)y* cellSize }, Color(0.4, 0.3, 0.2, 0.9))));

	auto build_grid2 = std::make_unique<Grid>(x, y, cellSize, Vector2{ x * cellSize + 64.f + 320, 128 });
	build_grid2->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(Vector2{ (float)x * cellSize, (float)y * cellSize }, Color(0.4, 0.3, 0.2, 0.9))));

	auto ball = std::make_unique<Ball>(Vector2(800, 450));
	//ball->AddComponent(std::make_unique<ShapeComponent>(std::make_unique<OpenGLRectangleShape>(Vector2(20), Color(0, 1, 0, 1))));
	//ball->AddComponent(std::make_unique<SpriteComponent>(std::make_unique<OpenGLSprite>(glm::vec2(64, 64), OpenGLRenderer::shaders_["colada_shader_sprite"], OpenGLRenderer::textures_["watermelon"])));
	ball->AddComponent(std::make_unique<RigidbodyComponent>(Vector2(64)));


	std::vector<std::shared_ptr<ISprite>> melonAnimation;
	for (int i = 0; i < 10; i++) {
		melonAnimation.push_back(std::make_unique<OpenGLSprite>(glm::vec2(16, 16), OpenGLRenderer::shaders_["colada_shader_sprite"], OpenGLRenderer::textures_["watermelon"]));
	}
	melonAnimation.push_back(std::make_unique<OpenGLSprite>(glm::vec2(16, 16), OpenGLRenderer::shaders_["colada_shader_sprite"], OpenGLRenderer::textures_["watermelon2"]));
	melonAnimation.push_back(std::make_unique<OpenGLSprite>(glm::vec2(16, 16), OpenGLRenderer::shaders_["colada_shader_sprite"], OpenGLRenderer::textures_["watermelon3"]));
	melonAnimation.push_back(std::make_unique<OpenGLSprite>(glm::vec2(16, 16), OpenGLRenderer::shaders_["colada_shader_sprite"], OpenGLRenderer::textures_["watermelon4"]));
	melonAnimation.push_back(std::make_unique<OpenGLSprite>(glm::vec2(16, 16), OpenGLRenderer::shaders_["colada_shader_sprite"], OpenGLRenderer::textures_["watermelon5"]));
	melonAnimation.push_back(std::make_unique<OpenGLSprite>(glm::vec2(16, 16), OpenGLRenderer::shaders_["colada_shader_sprite"], OpenGLRenderer::textures_["watermelon6"]));
	melonAnimation.push_back(std::make_unique<OpenGLSprite>(glm::vec2(16, 16), OpenGLRenderer::shaders_["colada_shader_sprite"], OpenGLRenderer::textures_["watermelon7"]));
	melonAnimation.push_back(std::make_unique<OpenGLSprite>(glm::vec2(16, 16), OpenGLRenderer::shaders_["colada_shader_sprite"], OpenGLRenderer::textures_["watermelon8"]));
	
	ball->AddComponent(std::make_unique<AnimatedSpriteComponent>(melonAnimation, 100000.0f));


	engine->AddGameObject(std::move(engine_debug_grid));
	engine->AddGameObject(std::move(background));
	engine->AddGameObject(std::move(xAxis));
	engine->AddGameObject(std::move(yAxis));
	engine->AddGameObject(std::move(gameManager));
	//engine->AddGameObject(std::move(cameraManager));


	engine->AddGameObject(std::move(build_grid1));
	engine->AddGameObject(std::move(build_grid2));
	engine->AddGameObject(std::move(ball));

	/*
	engine->AddGameObject(std::move(testCube));
	engine->AddGameObject(std::move(testCube1));
	engine->AddGameObject(std::move(testCube2));
	
	engine->AddGameObject(std::move(testSprite60x60));
	engine->AddGameObject(std::move(testSprite60x60_2));
	*/


	engine->StartGame();

	return 0;
}