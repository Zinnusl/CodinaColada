#pragma once

#include "IRenderer.h"
#include "IInput.h"

#include <memory>
#include <unordered_map>

class GameObject;
class IEngine
{
public:
	typedef int32_t idType;

	IEngine() = default;
	virtual ~IEngine() {}

	virtual void StartGame() = 0;
	virtual void StopGame() = 0;

	virtual void AddGameObject(std::unique_ptr<GameObject> gameobject) = 0;

	virtual IRenderer& GetRenderer() const = 0;
	virtual IInput& GetInput() const = 0;
};