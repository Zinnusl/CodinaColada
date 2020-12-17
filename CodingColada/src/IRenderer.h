#pragma once
#include "IShape.h"

class IRenderer
{
	virtual void Draw(IShape) = 0;
	virtual void OnClick(int x, int y) = 0;
};