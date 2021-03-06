#pragma once

#include "IShape.h"
#include "IInput.h"
#include "Vector2.h"

#include <memory>

class GameObject;
class IRenderer
{
public:
	virtual ~IRenderer() {}
	virtual void BeginFrame() = 0;
	virtual void Draw() = 0;
	virtual void EndFrame() = 0;
	virtual void OnClick(Vector2 clickPosition) = 0;
	virtual void AddShape(std::unique_ptr<IShape> shape) = 0;
	
	virtual void CreateWindow(int x, int y, IInput& input) = 0;
};