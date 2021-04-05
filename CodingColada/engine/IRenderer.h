#pragma once

#include "IShape.h"
#include "CodinaColadaWindow.h"
#include "Vector2.h"

#include <memory>

class GameObject;
class IRenderer
{
public:
	virtual ~IRenderer() {};
	virtual void BeginFrame() = 0;
	virtual void Draw(GameObject& gameobject, float subframe, float deltaTime) = 0;
	virtual void EndFrame() = 0;

	virtual void SetCameraPosition(Vector2 position) = 0;
	virtual Vector2 GetCameraPosition() = 0;
	virtual float GetZoom() = 0;
	virtual void SetZoom(float zoom) = 0;
	virtual Vector2 WorldToScreen(Vector2 worldPosition) = 0;
	virtual Vector2 ScreenToWorld(Vector2 screenPosition) = 0;

	//TODO. IInput needs a way to get the window so it can register for the input events
	virtual void* CreateWindow(int xResolution, int yResolution) = 0;
	virtual CodinaColadaWindow GetWindow() = 0;
};