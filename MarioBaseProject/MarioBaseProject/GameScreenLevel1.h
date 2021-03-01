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

	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;

	bool SetUpLevel1();
	void SetLevelMap();
	void DoScreenShake();
	LevelMap* m_level_map;
	Texture2D* m_background_texture;
	Character* my_character_mario;
	Character* my_character_luigi;
	PowBlock* m_pow_block;
	
};

#endif //_GAMESCREENLEVEL1_H