#include "ConsoleRenderer.h"

#define _WIN32_WINNT 0x0500 // 必要です。

#include <iostream>
#include <windows.h>

#undef CreateWindow

void ConsoleRenderer::Draw()
{
	//for (const auto& shape : shapes_)
	//{
//		shape->Draw();
	//}
}

void ConsoleRenderer::AddShape(std::unique_ptr<IShape> shape)
{
	shapes_.push_back(std::move(shape));
}

void ConsoleRenderer::CreateWindow(int x, int y, IInput& input)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	MoveWindow(console, r.left, r.top, x, y, TRUE);
}