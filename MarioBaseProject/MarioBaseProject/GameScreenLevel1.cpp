#include "GameScreenLevel1.h"
#include <iostream>





GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel1();
	m_level_map = nullptr;
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete m_background_texture;

	m_background_texture = nullptr;

	delete my_character_mario;

	my_character_mario = nullptr;

	delete my_character_luigi;

	my_character_luigi = nullptr;

	delete m_pow_block;

	m_pow_block = nullptr;
}

void GameScreenLevel1::Render() 
{
	//draw a background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);

	//Draw Mario
	my_character_mario->Render();

	//Draw Luigi
	my_character_luigi->Render();

	//Draw POW
	m_pow_block->Render();

	
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//update characters

	my_character_mario->Update(deltaTime, e);

	my_character_luigi->Update(deltaTime, e);

	//Circle Check collision (Mario and Luigi)
	if (Collisions::Instance()->Circle(my_character_mario->GetCollisionCircle(), my_character_luigi->GetCollisionCircle()))
	{
		std::cout << "Circle hit!" << std::endl;
	}

	//Box Check collision (Mario and Luigi)
	if (Collisions::Instance()->Box(my_character_mario->GetCollisionBox(), my_character_luigi->GetCollisionBox()))
	{
		std::cout << "Box hit!" << std::endl;
	}

	//Update POW
	UpdatePOWBlock();
};

bool GameScreenLevel1::SetUpLevel1()
{
	
	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	SetLevelMap();
	//set up player character
	my_character_mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map);
	
	//set up luigi
	my_character_luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(70, 330), m_level_map);

	return true;
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] =
	{ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	  {1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
	  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	  {0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
	  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	  {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
	  {1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
	  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };

	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	//set the new one
	m_level_map = new LevelMap(map);

	m_pow_block = new PowBlock(m_renderer, m_level_map);
}

void GameScreenLevel1::UpdatePOWBlock()
{
	if (Collisions::Instance()->Box(my_character_mario->GetCollisionBox(), m_pow_block->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailable())
		{
			if (my_character_mario->IsJumping())
			{
				/*DoScreenShake();*/
				m_pow_block->TakeHit();
				my_character_mario->CancelJump();
			}
		}
	}
}