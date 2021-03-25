#pragma once

#include "IRenderer.h"
#include "IInput.h"
#include "GameObject.h"

#include <memory>
#include <unordered_map>

class Engine
{
public:
	typedef int32_t idType;

protected:
	bool stopGame = false;
	std::unique_ptr<IRenderer> renderer_;
	std::unique_ptr<IInput> input_;

	
	std::unordered_map<idType, std::unique_ptr<GameObject>> gameobjects_;

public:

	Engine(std::unique_ptr<IRenderer> renderer, std::unique_ptr<IInput> input);
	~Engine() {}

	void StartGame();
	void StopGame();

	void AddGameObject(std::unique_ptr<GameObject> gameobject);

	IRenderer& GetRenderer() const;
	IInput& GetInput() const;
};