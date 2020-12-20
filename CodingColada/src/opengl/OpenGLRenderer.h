#pragma once

#include "../IRenderer.h"
#include "OpenGLShader.h"

#include <vector>
#include <memory>
#include <unordered_map>

class GLFWwindow;

class OpenGLRenderer : public IRenderer
{
protected:
	GLFWwindow* window_;
	std::vector<std::unique_ptr<IShape>> shapes_;
	

public:
	OpenGLRenderer();
	~OpenGLRenderer();

	static std::unordered_map<std::string, OpenGLShader> shaders_;

	virtual void Draw() override;
	virtual void AddShape(std::unique_ptr<IShape> shape) override;

	virtual void OnClick(Vector2 clickPosition) override;

	virtual void* CreateWindow(int x, int y) override;

	// Inherited via IRenderer
	virtual void RemoveShape(std::unique_ptr<IShape> shape) override;
};