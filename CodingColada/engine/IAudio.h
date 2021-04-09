#pragma once 

#include <string>

class IAudio
{
public:
	virtual void Play(std::string path, float volume, bool streamed) = 0;
	virtual void Loop(std::string path, float volume, bool streamed) = 0;
	virtual void Update() = 0;
};