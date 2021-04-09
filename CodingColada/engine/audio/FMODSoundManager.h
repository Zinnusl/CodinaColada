#pragma once

#include "../IAudio.h"
#include "fmod/fmod.hpp"

#include <memory>
#include <map>

class FMODSoundManager : public IAudio
{
	FMOD::System* system_ = nullptr;
	FMOD::Channel* channel_ = nullptr;

	std::map<std::string, FMOD::Sound*> soundMap_;
public:
	FMODSoundManager();
	virtual void Play(std::string path, float volume, bool streamed = true) override;
	virtual void Loop(std::string path, float volume, bool streamed = true) override;
	virtual void Update() override;
};