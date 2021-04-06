#pragma once
#include "IShape.h"

#include <vector>

#include "Vector2.h"
#include "OpenGLRenderer/Color.h"

class RectangleShape : public IShape
{
protected:
	Vector2 offset_;

	Vector2 size_;
	Color color_;

	std::vector<handlerCallbackType> clickHandlers_;

public:
	RectangleShape(Vector2 size, Color color);
	void OnClick(Vector2 clickPosition) override;
	void RegisterClickHandler(handlerCallbackType callback) override;
};