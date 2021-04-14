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
#include "SoundEffect.h"
#include "TextManager.h"
#include "GameScreenManager.h"



class Texture2D;

class Character;

class CharacterMario;

class CharacterLuigi;

class CharacterKoopa;

class CharacterGoomba;

class CharacterCoin;

class PowBlock;

class SoundEffect;

class TextManager;



class GameScreenLevel1 : GameScreen
{

public:

	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void UpdatePOWBlock();

private:

	int mariotext_x;
	int mariotext_y;
	int luigitext_x;
	int luigitext_y;
	int t_width_mario;
	int t_height_mario;
	int t_width_luigi;
	int t_height_luigi;
	int font_size;
	int player1_score_number;
	int player2_score_number;
	std::string player1_score;
	std::string player2_score;
	std::string font_path;
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
	//void DrawScore();

	LevelMap* m_level_map;
	Texture2D* m_map_texture;
	Texture2D* m_background_texture;
	Character* my_character_mario;
	Character* my_character_luigi;
	PowBlock* m_pow_block;
	std::vector<CharacterKoopa*> m_koopas;
	std::vector<CharacterCoin*> m_coins;
	std::vector<CharacterGoomba*> m_goombas;
	SoundEffect* m_pow_block_sound;
	SoundEffect* m_coin_collect;

	SDL_Color mario_text_color;
	SDL_Color luigi_text_color;
	
	
	TextManager* m_score_mario;
	TextManager* m_score_luigi;

	
	
	
};

#endif //_GAMESCREENLEVEL1_H