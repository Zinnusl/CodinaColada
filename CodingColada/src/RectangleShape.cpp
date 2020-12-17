#include "RectangleShape.h"

void RectangleShape::OnClick(Vector2 clickPosition)
{
	if (clickPosition.GetX() >= topLeft_.GetX() &&
		clickPosition.GetX() <= bottomRight_.GetX() &&
		clickPosition.GetY() >= topLeft_.GetY() &&
		clickPosition.GetY() <= bottomRight_.GetY())
	{
		//TODO removen
		printf("RectangleShape calls its callbacks\n");
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