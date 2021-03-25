#pragma once

#include "../IRenderer.h"

#include <vector>
#include <memory>

struct GLFWwindow;
class OpenGLRenderer : public IRenderer
{
protected:
	GLFWwindow* window_;
	std::vector<std::unique_ptr<IShape>> shapes_;

public:
	OpenGLRenderer();
	~OpenGLRenderer();


	virtual void Draw() override;
	virtual void AddShape(std::unique_ptr<IShape> shape) override;

	virtual void OnClick(Vector2 clickPosition) override;

	virtual void CreateWindow(int x, int y, IInput& input) override;
};