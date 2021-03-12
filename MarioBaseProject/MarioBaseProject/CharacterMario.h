#pragma once
#ifndef _CHARACTERMARIO_H
#define _CHARACTERMARIO_H

#include "Character.h"

class CharacterMario : public Character
{
protected:



	void Update(float deltaTime, SDL_Event e) override;
	

public:

	CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map);
	~CharacterMario();


	
	

private:

	
};


#endif _CHARACTERMARIO_H // _CHARACTERMARIO_H