#pragma once
#ifndef _CHARACTERCOIN_H
#define _CHARACTERCOIN_H

#include "Character.h"

class CharacterCoin : public Character
{
private:
	

	

	float m_frame_delay;
	float m_current_frame;

	

public:

	CharacterCoin(SDL_Renderer* renderer, std::string imagePath, LevelMap* map,
		Vector2D start_position, float frame_delay);
	~CharacterCoin();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

	void FlipRightwayUp();
	
	void Jump();
};

#endif _CHARACTERCOIN_H
