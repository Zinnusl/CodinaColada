#pragma once

#include "../IRenderer.h"

#include <vector>
#include <memory>
#include <unordered_map>

class GLFWwindow;
class OpenGLShader;
class OpenGLRenderer : public IRenderer
{
protected:
	GLFWwindow* window_;
	std::vector<std::unique_ptr<IShape>> shapes_;
	std::unordered_map<std::string, std::unique_ptr<OpenGLShader>> shaders_;

	unsigned int shaderProgram;

public:
	OpenGLRenderer();
	~OpenGLRenderer();


	virtual void Draw() override;
	virtual void AddShape(std::unique_ptr<IShape> shape) override;

	virtual void OnClick(Vector2 clickPosition) override;

	virtual void* CreateWindow(int x, int y) override;
};