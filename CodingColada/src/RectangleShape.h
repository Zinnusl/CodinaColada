#pragma once
#include "IShape.h"

#include <vector>

#include "Vector2.h"

class RectangleShape : public IShape
{
protected:
	Vector2 topLeft_;
	Vector2 bottomRight_;

	std::vector<handlerCallbackType> clickHandlers_;

public:
	RectangleShape(Vector2 topLeft, Vector2 bottomRight);
	void OnClick(Vector2 clickPosition) override;
	void RegisterClickHandler(handlerCallbackType callback) override;
	void Draw() override;
};