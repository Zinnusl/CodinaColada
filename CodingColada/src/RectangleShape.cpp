#include "RectangleShape.h"

RectangleShape::RectangleShape(Vector2 topLeft, Vector2 bottomRight)
	: topLeft_(topLeft), bottomRight_(bottomRight)
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

void RectangleShape::Draw()
{
}