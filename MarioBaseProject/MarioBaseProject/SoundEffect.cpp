#include "SoundEffect.h"

SoundEffect::SoundEffect()
{
	
}

SoundEffect::~SoundEffect()
{
	SDL_CloseAudioDevice(deviceId);
	SDL_FreeWAV(wavBuffer);
}

void SoundEffect::Play()
{
	//Play audio till end
	SDL_QueueAudio(deviceId, wavBuffer, wavLength);
	SDL_PauseAudioDevice(deviceId, 0);
}

void SoundEffect::Load(const char* path)
{
	//Load WAV sounds
	SDL_LoadWAV(path, &wavSpec, &wavBuffer, &wavLength);
	deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
}