#include "CameraManager.h"

#include "../../engine/Engine.h"
#include "imgui.h"

CameraManager::CameraManager()
{
}

void CameraManager::OnDraw(float deltaTime)
{
	#define 	GLFW_KEY_RIGHT   262
	#define 	GLFW_KEY_LEFT   263
	#define 	GLFW_KEY_DOWN   264
	#define 	GLFW_KEY_UP   265

	IInput& input = engine_->GetInput();
	IRenderer& renderer = engine_->GetRenderer();
	Vector2 cameraPosition = renderer.GetCameraPosition();
	if (input.GetKey(GLFW_KEY_RIGHT))
	{
		cameraPosition.SetX(cameraPosition.GetX() + 0.001f);
	}
	if (input.GetKey(GLFW_KEY_LEFT))
	{
		cameraPosition.SetX(cameraPosition.GetX() - 0.001f);
	}
	if (input.GetKey(GLFW_KEY_UP))
	{
		cameraPosition.SetY(cameraPosition.GetY() + 0.001f);
	}
	if (input.GetKey(GLFW_KEY_DOWN))
	{
		cameraPosition.SetY(cameraPosition.GetY() - 0.001f);
	}
	renderer.SetCameraPosition(cameraPosition);

	int scrollWheel = input.GetScrollWheel();
	float newZoom = renderer.GetZoom() + scrollWheel / 10.f;
	if (newZoom < 0.01f)
	{
		newZoom = 0.01f;
	}
	if (newZoom > 10)
	{
		newZoom = 10;
	}
	renderer.SetZoom(newZoom);
}

void CameraManager::OnDebugTreeNode()
{
	IRenderer& renderer = engine_->GetRenderer();
	ImGui::Text("Zoom %f", renderer.GetZoom());
}
