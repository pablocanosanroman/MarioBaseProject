#pragma once
#ifndef GAMESCREENLEVEL1_H
#define GAMESCREENLEVEL1_H

#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"

class Texture2D;

class Character;

class GameScreenLevel1 : GameScreen
{

public:

	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

private:

	bool SetUpLevel1();
	Texture2D* m_background_texture;
	Character* my_character;
	
};

#endif //_GAMESCREENLEVEL1_H