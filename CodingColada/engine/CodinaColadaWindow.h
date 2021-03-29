#pragma once

#include "Vector2.h"

//TODO Is this class absolete? Can we move this in the IRenderer?
class CodinaColadaWindow
{
	Vector2 resolution_;
public:
	CodinaColadaWindow() = delete;
	CodinaColadaWindow(Vector2 resolution);
	Vector2 GetResolution();
};