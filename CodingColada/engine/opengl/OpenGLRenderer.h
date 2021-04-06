#pragma once

#include "../IRenderer.h"
#include "OpenGLShader.h"
#include "OpenGLTexture2D.h"

#include <vector>
#include <memory>
#include <unordered_map>


class GLFWwindow;
class OpenGLRenderer : public IRenderer
{
	//Defines how many engine units a full viewport is
	glm::vec2 engineUnitsOnOneScreen_;

	//Projects the ingame units to normalized opengl coordinates ([-1,1])
	glm::mat4 projection_;

	//Position of the camera in engine units (EU)
	glm::vec2 cameraPosition_;

	//The zoom value scaled the displayed content. Higher values equal closer.
	//TODO what is the origin of the zoom? Should it be changeable?
	float zoom_;

	int width_;
	int height_;
	GLFWwindow* window_;

public:
	OpenGLRenderer();
	~OpenGLRenderer();

	static std::unordered_map<std::string, OpenGLShader> shaders_;
	static std::unordered_map<std::string, OpenGLTexture2D> textures_;

	void LoadShader(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath, std::function<void(OpenGLShader&)> onUseCallback = {});
	void LoadTexture(std::string name, std::string file, bool alpha = true);

	virtual void* CreateWindow(int xResolution, int yResolution, int xEngineUnits, int yEngineUnits) override;

	// Inherited via IRenderer
	virtual void BeginFrame() override;
	virtual void Draw(GameObject& gameobject, float subframe, float deltaTime) override;
	virtual void EndFrame() override;
	virtual Vector2 GetResolution() override;
	virtual void SetCameraPosition(Vector2 position) override;
	virtual Vector2 GetCameraPosition() override;
	virtual float GetZoom() override;
	virtual void SetZoom(float zoom) override;
	virtual Vector2 WorldToScreen(Vector2 worldPosition) override;
	virtual Vector2 ScreenToWorld(Vector2 screenPosition) override;
	virtual Vector2 GetEUResolution() override;
};