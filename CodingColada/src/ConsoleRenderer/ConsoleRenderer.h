#pragma once

#include <vector>
#include "../IRenderer.h"

class ConsoleRenderer : public IRenderer
{
protected:
	std::vector<std::unique_ptr<IShape>> shapes_;

public:
	explicit ConsoleRenderer() = default;
	~ConsoleRenderer() = default;

	virtual void Draw() override;
	virtual void BeginFrame() override {}
	virtual void EndFrame() override {}
	virtual void AddShape(std::unique_ptr<IShape> shape) override;
	virtual void OnClick(Vector2 clickPosition) override
	{}

	virtual void CreateWindow(int x, int y, IInput& input) override;
};