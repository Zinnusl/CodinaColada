#pragma once

#include "IRenderer.h"

class IEngine
{
public:

	virtual void CreateWindow(const int size_x, const int size_y) = 0;
	virtual IRenderer* GetRenderer() const = 0;
};