#include "RectangleShape.h"



RectangleShape::RectangleShape(Vector2 size, Color color)
	: size_(size), color_(color)
{
	
}

void RectangleShape::OnClick(Vector2 clickPosition)
{
	
}

void RectangleShape::RegisterClickHandler(handlerCallbackType callback)
{
	clickHandlers_.push_back(callback);
}
