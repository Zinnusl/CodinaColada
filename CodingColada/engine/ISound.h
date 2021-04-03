#include <string>

class ISound
{
protected:
	virtual void Play(std::string path, float volume) = 0;
	virtual void Loop(std::string path, float volume) = 0;
};