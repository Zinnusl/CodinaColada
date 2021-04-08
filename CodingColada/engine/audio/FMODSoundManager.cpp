#include "FMODSoundManager.h"


FMODSoundManager::FMODSoundManager()
{
	FMOD::System_Create(&system_);
	system_->init(128, FMOD_INIT_NORMAL, nullptr);
}

void FMODSoundManager::Play(std::string path, float volume)
{
	auto iterator = soundMap_.find(path);
	if (iterator == soundMap_.end())
	{
		//Load audio
		FMOD::Sound* pSound = nullptr;
		system_->createSound(path.c_str(), FMOD_DEFAULT, nullptr, &pSound);
		soundMap_.emplace(path, pSound);
		system_->playSound(pSound, nullptr, false, &channel_);
	}
	else
	{
		system_->playSound(iterator->second, nullptr, false, &channel_);
	}
}

void FMODSoundManager::Loop(std::string path, float volume)
{
}

void FMODSoundManager::Update()
{
	//bool bIsPlaying = true;
	//while (bIsPlaying) {
	//	pChannel->isPlaying(&bIsPlaying);
	system_->update();
	//}
}
