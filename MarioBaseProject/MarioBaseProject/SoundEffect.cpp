#include "SoundEffect.h"

SoundEffect::SoundEffect()
{
	SDL_Init(SDL_INIT_AUDIO);
}

SoundEffect::~SoundEffect()
{
	SDL_CloseAudioDevice(deviceId);
	SDL_FreeWAV(wavBuffer);
}

void SoundEffect::Play()
{
	SDL_QueueAudio(deviceId, wavBuffer, wavLength);
	SDL_PauseAudioDevice(deviceId, 0);
}

void SoundEffect::Load(const char* path)
{
	SDL_LoadWAV(path, &wavSpec, &wavBuffer, &wavLength);
	deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
}