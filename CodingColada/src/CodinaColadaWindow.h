#pragma once

#include "Vector2.h"

class CodinaColadaWindow
{
	Vector2 resolution_;
public:
	CodinaColadaWindow() = delete;
	CodinaColadaWindow(Vector2 resolution);
	Vector2 GetResolution();
};