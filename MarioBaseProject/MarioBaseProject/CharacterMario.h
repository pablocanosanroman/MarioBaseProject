#pragma once
#ifndef _CHARACTERMARIO_H
#define _CHARACTERMARIO_H

#include "Character.h"
#include "SoundEffect.h"

class CharacterMario : public Character
{
protected:



	void Update(float deltaTime, SDL_Event e) override;
	void Render() override;

	

public:

	CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map, float frame_delay);
	~CharacterMario();

	


	
	

private:
	
	float m_frame_delay;
	float m_current_frame;
	
};


#endif _CHARACTERMARIO_H // _CHARACTERMARIO_H