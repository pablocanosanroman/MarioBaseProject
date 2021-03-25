#pragma once
#ifndef _SOUNDEFFECT_H_
#define _SOUNDEFFECT_H_

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include "Commons.h"

class SoundEffect
{
public:
	SoundEffect();
	~SoundEffect();

	void Play();
	void Load(const char* path);

	
private:
	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8 *wavBuffer;
	SDL_AudioDeviceID deviceId;
};
	

#endif // !_SOUNDEFFECT_H_



