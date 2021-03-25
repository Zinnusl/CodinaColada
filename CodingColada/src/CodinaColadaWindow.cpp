#pragma once

#include "Vector2.h"
#include "CodinaColadaWindow.h"


CodinaColadaWindow::CodinaColadaWindow(Vector2 resolution)
	: resolution_(resolution)
{
}

Vector2 CodinaColadaWindow::GetResolution()
{
	return resolution_;
}