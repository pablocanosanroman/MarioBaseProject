#pragma once
#ifndef GAMESCREENLEVEL1_H
#define GAMESCREENLEVEL1_H

#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "Collisions.h"
#include "LevelMap.h"
#include "PowBlock.h"

class Texture2D;

class Character;

class CharacterMario;

class CharacterLuigi;

class PowBlock;

class GameScreenLevel1 : GameScreen
{

public:

	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void UpdatePOWBlock();

private:

	bool SetUpLevel1();
	void SetLevelMap();
	LevelMap* m_level_map;
	Texture2D* m_background_texture;
	Character* my_character_mario;
	Character* my_character_luigi;
	PowBlock* m_pow_block;
	
};

#endif //_GAMESCREENLEVEL1_H