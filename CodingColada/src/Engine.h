#pragma once

#include <memory>
#include <unordered_map>

#include "IEngine.h"
#include "GameObject.h"

class Engine : public IEngine
{
public:
	typedef int32_t idType;
	const int8_t physicTickrate = 60;
	const float physicsStepsPerSecond = 1.f / physicTickrate;

protected:
	bool stopGame = false;
	IRenderer& renderer_;
	IInput& input_;
		
	std::unordered_map<idType, std::unique_ptr<GameObject>> gameobjects_;

public:
	Engine(IRenderer& renderer, IInput& input);
	~Engine() {}

	void StartGame();
	void StopGame();

	void AddGameObject(std::unique_ptr<GameObject> gameobject);

	IRenderer& GetRenderer() const;
	IInput& GetInput() const;
};