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
protected:
	GLFWwindow* window_;

public:
	OpenGLRenderer();
	~OpenGLRenderer();

	static std::unordered_map<std::string, OpenGLShader> shaders_;
	static std::unordered_map<std::string, OpenGLTexture2D> textures_;


	virtual void OnClick(Vector2 clickPosition) override;

	virtual void* CreateWindow(int x, int y) override;

	GLFWwindow* GetWindow();

	// Inherited via IRenderer
	void BeginFrame() override;
	void Draw(GameObject& gameobject, float subframe) override;
	void EndFrame() override;
};