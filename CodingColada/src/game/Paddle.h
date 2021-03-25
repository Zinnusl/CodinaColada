#include "../GameObject.h"

class Paddle : public GameObject
{
	float speed = 0.001;
public:
	Paddle();
	
	Paddle(Vector2 position);
	
	void OnUpdate(float deltaTime) override;
	void OnDebugTreeNode() override;
};