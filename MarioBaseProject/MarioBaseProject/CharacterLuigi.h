#pragma once
#ifndef _CHARACTERLUIGI_H
#define _CHARACTERLUIGI_H


#include "Character.h"

class CharacterLuigi : public Character
{
protected:



	void Update(float deltaTime, SDL_Event e) override;
	

public:

	CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position);
	~CharacterLuigi();

	
	

private:

	
};

#endif _CHARACTERLUIGI_H // _CHARACTERLUIGI_H

