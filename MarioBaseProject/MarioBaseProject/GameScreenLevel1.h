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
#include "CharacterKoopa.h"
#include "CharacterCoin.h"
#include "CharacterGoomba.h"



#include <vector>

class Texture2D;

class Character;

class CharacterMario;

class CharacterLuigi;

class CharacterKoopa;

class CharacterGoomba;

class CharacterCoin;

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
	float timeForNextKoopa;
	int countKoopa;

	bool SetUpLevel1();
	void SetLevelMap();
	void DoScreenShake();
	void UpdateKoopas(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void UpdateCoins(float deltaTime, SDL_Event e);
	void CreateCoins(Vector2D position, float frame_delay);
	void UpdateGoombas(float deltaTime, SDL_Event e);
	void CreateGoombas(Vector2D position, FACING direction, float speed, float frame_delay);
	LevelMap* m_level_map;
	Texture2D* m_background_texture;
	Character* my_character_mario;
	Character* my_character_luigi;
	PowBlock* m_pow_block;
	std::vector<CharacterKoopa*> m_koopas;
	std::vector<CharacterCoin*> m_coins;
	std::vector<CharacterGoomba*> m_goombas;
	
	
	
	
};

#endif //_GAMESCREENLEVEL1_H