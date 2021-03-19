#pragma once
#ifndef _CHARACTERGOOMBA_H
#define _CHARACTERGOOMBA_H

#include "Character.h"

class CharacterGoomba : public Character
{
private:
	
	float m_frame_delay;
	float m_current_frame;

public:
	CharacterGoomba(SDL_Renderer* renderer, std::string imagePath, LevelMap* map,
		Vector2D start_position, FACING start_facing, float movement_speed, float frame_delay);

	~CharacterGoomba();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

	
	
};

#endif // !_CHARACTERGOOMBA_H



