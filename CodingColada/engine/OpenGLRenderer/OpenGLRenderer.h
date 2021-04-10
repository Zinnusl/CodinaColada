#pragma once

#include "../IRenderer.h"
#include "OpenGLShader.h"
#include "OpenGLTexture2D.h"

#include <vector>
#include <memory>
#include <unordered_map>

struct GLFWwindow;

class OpenGLRenderer : public IRenderer
{
protected:
	GLFWwindow* window_;

	std::unordered_map<std::string, OpenGLShader> shaders_;
	std::unordered_map<std::string, OpenGLTexture2D> textures_;
	std::vector<std::unique_ptr<IShape>> shapes_;

public:
	OpenGLRenderer();
	~OpenGLRenderer();

	virtual void OnClick(Vector2 clickPosition) override;

	virtual void CreateWindow(int x, int y, IInput&) override;

	virtual void AddShape(std::unique_ptr<IShape> shape)
	{
		shapes_.push_back(std::move(shape));
	}

	OpenGLShader& GetShader(std::string shader_name)
	{
		return shaders_[shader_name];
	}

	OpenGLTexture2D& GetTexture(std::string texture_name)
	{
		return textures_[texture_name];
	}

	GLFWwindow* GetWindow();

	// Inherited via IRenderer
	void BeginFrame() override;
	void Draw() override;
	void EndFrame() override;
};