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
	//This is a shared pointer so we can set up shaders.. We need a reference that know its an OpenGLRendere in ClientApp. We need to load shaders after creating the window because the projectiond epends on the window (or does it?)
	std::shared_ptr<IRenderer> renderer_;
	std::unique_ptr<IInput> input_;

	
	std::unordered_map<idType, std::unique_ptr<GameObject>> gameobjects_;

public:

	Engine(std::shared_ptr<IRenderer> renderer, std::unique_ptr<IInput> input);
	~Engine() {}

	void StartGame();
	void StopGame();
	bool IsStopped();

	void AddGameObject(std::unique_ptr<GameObject> gameobject);

	IRenderer& GetRenderer() const;
	IInput& GetInput() const;
};