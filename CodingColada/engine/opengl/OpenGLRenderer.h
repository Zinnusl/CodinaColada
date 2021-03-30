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
	glm::mat4 projection_;
	glm::vec2 cameraPosition_;
	float zoom_;

protected:
	GLFWwindow* window_;

public:
	OpenGLRenderer();
	~OpenGLRenderer();

	static std::unordered_map<std::string, OpenGLShader> shaders_;
	static std::unordered_map<std::string, OpenGLTexture2D> textures_;

	void LoadShader(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath);
	void LoadTexture(std::string name, std::string file, bool alpha = true);

	virtual void* CreateWindow(int x, int y) override;


	// Inherited via IRenderer
	void BeginFrame() override;
	void Draw(GameObject& gameobject, float subframe) override;
	void EndFrame() override;

	// Inherited via IRenderer
	virtual CodinaColadaWindow GetWindow() override;

	virtual void SetCameraPosition(Vector2 position) override;
	virtual Vector2 GetCameraPosition() override;

	virtual float GetZoom() override;
	virtual void SetZoom(float zoom) override;
};