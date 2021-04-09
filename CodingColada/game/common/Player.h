#include <string>

class Player
{
	int32_t playerId_;
	std::string name_;
	int32_t score_;

public:
	int32_t GetPlayerId();
	std::string GetName();
	int32_t GetScore();
};