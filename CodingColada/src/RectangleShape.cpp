#include "RectangleShape.h"



RectangleShape::RectangleShape(Vector2 size, Color color)
	: size_(size), color_(color)
{
	
}

void RectangleShape::OnClick(Vector2 clickPosition)
{
	if (clickPosition.GetX() >= topLeft_.GetX() &&
		clickPosition.GetX() <= bottomRight_.GetX() &&
		clickPosition.GetY() >= topLeft_.GetY() &&
		clickPosition.GetY() <= bottomRight_.GetY())
	{
		for (const auto& callback : clickHandlers_)
		{
			callback();
		}
	}
}

void RectangleShape::RegisterClickHandler(handlerCallbackType callback)
{
	clickHandlers_.push_back(callback);
}
