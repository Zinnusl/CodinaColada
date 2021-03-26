#include "../../GameObject.h"

class Tower : public GameObject
{
	float speed = 0.001;
public:
	Tower() = delete;

	Tower(Vector2 position);

	void OnPhysicsUpdate(float deltaTime) override;
	void OnDebugTreeNode() override;
	void OnDraw(float subframe) override;
};