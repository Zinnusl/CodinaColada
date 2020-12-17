#pragma once

#include "IEngine.h"


class GLFWwindow;
class Openglengine : public IEngine
{
protected:
	GLFWwindow* window_;
	IRenderer* renderer_;

public:
	Openglengine();
	~Openglengine();

	void CreateWindow(const int size_x, const int size_y);
	IRenderer* GetRenderer() const;
};