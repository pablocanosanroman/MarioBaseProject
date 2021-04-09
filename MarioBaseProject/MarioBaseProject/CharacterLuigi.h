#pragma once
#ifndef _CHARACTERLUIGI_H
#define _CHARACTERLUIGI_H


#include "Character.h"

class CharacterLuigi : public Character
{
protected:



	void Update(float deltaTime, SDL_Event e) override;
	void Render() override;

public:

	CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map, float frame_delay);
	~CharacterLuigi();

	
	
private:

	float m_frame_delay;
	float m_current_frame;

	
};

#endif _CHARACTERLUIGI_H // _CHARACTERLUIGI_H

