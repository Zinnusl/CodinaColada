#pragma once

#include "IShape.h"
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
	virtual Vector2 GetResolution() = 0;
	virtual Vector2 GetEUResolution() = 0; //Resolution in EngineUnits
	virtual Vector2 WorldToScreen(Vector2 worldPosition) = 0;
	virtual Vector2 ScreenToWorld(Vector2 screenPosition) = 0;
	virtual Vector2 EuToPixel(Vector2 pixels) = 0;

	//TODO. IInput needs a way to get the window so it can register for the input events
	virtual void* CreateWindow(int xResolution, int yResolution, int xEngineUnits, int yEngineUnits, bool fullscreen) = 0;
};