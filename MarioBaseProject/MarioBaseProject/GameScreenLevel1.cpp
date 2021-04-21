#include "GameScreenLevel1.h"
#include <iostream>
#include <sstream>






GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel1();
	timeForNextKoopa = KOOPA_SPAWN_TIME;
	
}

GameScreenLevel1::~GameScreenLevel1()
{
	//Delete all the variables


	delete m_map_texture;

	m_map_texture = nullptr;

	delete my_character_mario;

	my_character_mario = nullptr;

	delete my_character_luigi;

	my_character_luigi = nullptr;

	delete m_pow_block;

	m_pow_block = nullptr;

	m_koopas.clear();

	m_coins.clear();

	m_goombas.clear();

	delete m_pow_block_sound;

	delete m_coin_collect;

	delete m_level_map;

	m_level_map = nullptr;

	delete m_score_mario;

	delete m_score_luigi;

	
}

void GameScreenLevel1::Render() 
{
	//Draw the background texture 
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);

	//draw the koopas
	for (int i = 0; i < m_koopas.size(); i++)
	{
		m_koopas[i]->Render();
	}

	//draw the coins
	for (int i = 0; i < m_coins.size(); i++)
	{
		m_coins[i]->Render();
	}

	//draw the goombas
	for (int i = 0; i < m_goombas.size(); i++)
	{
		m_goombas[i]->Render();
	}

	//draw the map
	m_map_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);

	//Draw Mario
	my_character_mario->Render();

	//Draw Luigi
	my_character_luigi->Render();

	//Draw POW
	m_pow_block->Render();


	m_score_mario->Render(mariotext_x, mariotext_y, m_renderer);


	//SDL_RenderCopy(m_renderer, ftext_texture_mario, NULL, &mario_dst);


	//SDL_RenderCopy(m_renderer, ftext_texture_luigi, NULL, &luigi_dst);
	m_score_luigi->Render(luigitext_x, luigitext_y, m_renderer);



	
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	
	//Update player score
	player1_score = std::to_string(player1_score_number);
	player2_score = std::to_string(player2_score_number);

	//do the screen shake if required
	if (m_screenshake)
	{
		
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble); //wobble = tambalearse
		m_background_yPos *= 3.0f;

		//end shake after duration
		if (m_shake_time <= 0.0f)
		{
			m_shake_time = false;
			m_background_yPos = 0.0f;
		}
	}
	//update characters

	my_character_mario->Update(deltaTime, e);

	my_character_luigi->Update(deltaTime, e);

	//Update score texts
	m_score_mario = new TextManager(m_renderer, font_size, font_path, player1_score, mario_text_color);
	m_score_luigi = new TextManager(m_renderer, font_size, font_path, player2_score, luigi_text_color);

	
	

	//Circle Check collision (Mario and Luigi)
	if (Collisions::Instance()->Circle(my_character_mario->GetCollisionCircle(), my_character_luigi->GetCollisionCircle()))
	{
		std::cout << "Circle hit!" << std::endl;
	}

	//Box Check collision (Mario and Luigi)
	if (Collisions::Instance()->Box(my_character_mario->GetCollisionBoxPlayer(), my_character_luigi->GetCollisionBox()))
	{
		std::cout << "Box hit!" << std::endl;
	}

	//Update POW
	UpdatePOWBlock();
	//Update Koopas
	UpdateKoopas(deltaTime, e);
	//Update Coins
	UpdateCoins(deltaTime, e);
	//Update Goombas
	UpdateGoombas(deltaTime, e);

	timeForNextKoopa -= deltaTime;
	
	//Spawn 2 more koopas 5 times
	
	if (timeForNextKoopa <= 0.0f && countKoopa < 5)
	{
			countKoopa++;
			timeForNextKoopa = KOOPA_SPAWN_TIME;
			CreateKoopa(Vector2D(90, 32), FACING_RIGHT, KOOPA_SPEED);
			CreateKoopa(Vector2D(425, 32), FACING_LEFT, KOOPA_SPEED);
	}

	GameOver(deltaTime, e);
	
	Victory(deltaTime, e);
	
	
};

bool GameScreenLevel1::SetUpLevel1()
{
	
	//Initialize screenshake when the pow block is hit
	m_screenshake = false;

	//Initialize y position of the background, so it can be move when the screenshake happens
	m_background_yPos = 0.0f;

	//Initialize score of both players
	player1_score_number = 0;
	player2_score_number = 0;
	player1_score = std::to_string(player1_score_number);
	player2_score = std::to_string(player2_score_number);

	mariotext_x = 70;
	mariotext_y = 0;

	luigitext_x = SCREEN_WIDTH - 140;
	luigitext_y = 0;

	//width and height
	t_width_mario = 0;
	t_height_mario = 0;
	t_width_luigi = 0;
	t_height_luigi = 0;
	
	//Color of the texts
	mario_text_color = { 255, 0, 0 };
	luigi_text_color = { 0, 255, 0 };

	//size of font
	font_size = 20;
	
	//Font path
	font_path = "Fonts/MarioFont.ttf";

	//Initialize score texts
	m_score_mario = new TextManager(m_renderer, font_size, font_path, player1_score, mario_text_color);
	m_score_luigi = new TextManager(m_renderer, font_size, font_path, player2_score, luigi_text_color);
	
	//load background texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/black.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;

	}

	//load map texture
	m_map_texture = new Texture2D(m_renderer);
	if (!m_map_texture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Failed to load map texture!" << std::endl;
		return false;
	}

	//Set up sound
	m_pow_block_sound = new SoundEffect();
	m_pow_block_sound->Load("Music/PowBlockHit.wav");
	
	m_coin_collect = new SoundEffect();
	m_coin_collect->Load("Music/coin.wav");


	SetLevelMap();
	//set up player character
	my_character_mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 130), m_level_map, ANIMATION_DELAY);
	
	
	
	//set up luigi
	my_character_luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(70, 130), m_level_map, ANIMATION_DELAY);

	//set up koopas
	CreateKoopa(Vector2D(90, -150), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(425, -150), FACING_LEFT, KOOPA_SPEED);

	//Set up coins

	// First Platforms
	CreateCoins(Vector2D(160, 40), ANIMATION_DELAY);
	CreateCoins(Vector2D(335, 40), ANIMATION_DELAY);

	//Middle Platform
	CreateCoins(Vector2D(140, 135), ANIMATION_DELAY);
	CreateCoins(Vector2D(180, 135), ANIMATION_DELAY);
	CreateCoins(Vector2D(220, 135), ANIMATION_DELAY);
	CreateCoins(Vector2D(260, 135), ANIMATION_DELAY);
	CreateCoins(Vector2D(300, 135), ANIMATION_DELAY);
	CreateCoins(Vector2D(340, 135), ANIMATION_DELAY);

	//Small Platforms
	CreateCoins(Vector2D(45, 160), ANIMATION_DELAY);
	CreateCoins(Vector2D(450, 160), ANIMATION_DELAY);
	

	//Set up Goombas
	CreateGoombas(Vector2D(120, 20), FACING_RIGHT, GOOMBA_SPEED, ANIMATION_DELAY);
	CreateGoombas(Vector2D(355, 20), FACING_LEFT, GOOMBA_SPEED, ANIMATION_DELAY);



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
	//Collisison between pow block and mario
	if (Collisions::Instance()->Box(my_character_mario->GetCollisionBoxPlayer(), m_pow_block->GetCollisionBox()))
	{
		
		if (m_pow_block->IsAvailable())
		{
			m_pow_block_sound->Play();
			if (my_character_mario->IsJumping())
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				my_character_mario->CancelJump();
			}
		}
	}

	//Collisison between pow block and luigi
	if (Collisions::Instance()->Box(my_character_luigi->GetCollisionBoxPlayer(), m_pow_block->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailable())
		{
			m_pow_block_sound->Play();
			if (my_character_luigi->IsJumping())
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				my_character_luigi->CancelJump();
			}
		}
	}
}

void GameScreenLevel1::UpdateKoopas(float deltaTime, SDL_Event e)
{
	if (!m_koopas.empty())
	{
		int koopasIndexToDelete = -1;
		for (unsigned int i = 0; i < m_koopas.size(); i++)
		{
			//check if the enemy is on the bottom row of tiles
			if (m_koopas[i]->GetPosition().y > 300.0f)
			{
				//is the enemy off screen to the left/right?
				if (m_koopas[i]->GetPosition().x + m_koopas[i]->GetWidthSprite() < 1 ||
					m_koopas[i]->GetPosition().x > SCREEN_WIDTH)
				{
					m_koopas[i]->SetAlive(false);
				}

			}
			//now do the update
			m_koopas[i]->Update(deltaTime, e);

			//check to see if enemy collides with player
			if ((m_koopas[i]->GetPosition().y > 300.0f ||
				m_koopas[i]->GetPosition().y <= 64.0f) && (m_koopas[i]->GetPosition().x < 64.0f ||
					m_koopas[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//ignore collisions if behind pipe
			}
			else
			{
				//Collision between koopas, Mario and Luigi
				if (Collisions::Instance()->Circle(m_koopas[i]->GetCollisionCircle(), my_character_mario->GetCollisionCircle()))
				{
					if (m_koopas[i]->GetInjured())
					{
						m_koopas[i]->SetAlive(false);
						player1_score_number += 300;
						
						
					}
					else
					{
						my_character_mario->death();
						my_character_mario->SetAlive(false);
						
					}
				}

				if (Collisions::Instance()->Circle(m_koopas[i]->GetCollisionCircle(), my_character_luigi->GetCollisionCircle()))
				{
					if (m_koopas[i]->GetInjured())
					{
						m_koopas[i]->SetAlive(false);
						player2_score_number += 300;
						
					}
					else
					{
						my_character_luigi->death();
						my_character_luigi->SetAlive(false);
					}
				}


				
			}

			//if the enemy is no longer alive then schedule it for deletion
			if (!m_koopas[i]->GetAlive())
			{
				koopasIndexToDelete = i;
			}

			
		}
			//remove dead enemies -1 each update
		if (koopasIndexToDelete != -1)
		{
			m_koopas.erase(m_koopas.begin() + koopasIndexToDelete);
		}
		
	}
}

void GameScreenLevel1::UpdateCoins(float deltaTime, SDL_Event e)
{
	if (!m_coins.empty())
	{
		int coinsIndexToDelete = -1;

		for (unsigned int i = 0; i < m_coins.size(); i++)
		{
			//Check if the coin is in the bottom row of tiles
			if (m_coins[i]->GetPosition().y > 300.0f)
			{
				if (m_coins[i]->GetPosition().x < (float)(-m_coins[i]->GetCollisionBox().width * 0.5f) ||
					m_coins[i]->GetPosition().x > SCREEN_WIDTH - (float)(m_coins[i]->GetCollisionBox().width * 0.55f))
				{
					m_coins[i]->SetAlive(false);
				}
			}

			//Update
			m_coins[i]->Update(deltaTime, e);

			//check to see if coin collides with player
			if ((m_coins[i]->GetPosition().y > 300.0f || m_coins[i]->GetPosition().y <= 64.0f) &&
				(m_coins[i]->GetPosition().x < 64.0f || m_coins[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{

			}
			else
			{
				if (Collisions::Instance()->Circle(m_coins[i]->GetCollisionCircle(), my_character_mario->GetCollisionCircle()))
				{
					if (m_coins[i]->GetAlive())
					{
						m_coin_collect->Play();
					}

					
					m_coins[i]->SetAlive(false);
					player1_score_number += 200;
					
					
				}

				if (Collisions::Instance()->Circle(m_coins[i]->GetCollisionCircle(), my_character_luigi->GetCollisionCircle()))
				{
					if (m_coins[i]->GetAlive())
					{
						m_coin_collect->Play();
					}

				
					m_coins[i]->SetAlive(false);
					player2_score_number += 200;
					
				
				}
			}

			//if the enemy is no longer alive then schedule it for deletion
			if (!m_coins[i]->GetAlive())
			{
				coinsIndexToDelete = i;
			}
			
		}

		//remove dead enemies -1 each update

		if (coinsIndexToDelete != -1)
		{
			m_coins.erase(m_coins.begin() + coinsIndexToDelete);
		}
	}
	
}

void GameScreenLevel1::UpdateGoombas(float deltaTime, SDL_Event e)
{
	if (!m_goombas.empty())
	{
		int goombasIndexToDelete = -1;

		for (unsigned int i = 0; i < m_goombas.size(); i++)
		{
			//check if the enemy is on the bottom row of tiles
			if (m_goombas[i]->GetPosition().y > 300.0f)
			{
				//is the enemy off screen to the left/right?
				if (m_goombas[i]->GetPosition().x + m_koopas[i]->GetWidthSprite() < 0 ||
					m_goombas[i]->GetPosition().x > SCREEN_WIDTH)
				{
					m_goombas[i]->SetAlive(false);
				}

			}
			//now do the update
			m_goombas[i]->Update(deltaTime, e);

			//check to see if enemy collides with player
			if ((m_goombas[i]->GetPosition().y > 300.0f ||
				m_goombas[i]->GetPosition().y <= 64.0f) && (m_goombas[i]->GetPosition().x < 64.0f ||
					m_goombas[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//ignore collisions if behind pipe
			}
			else
			{
				//Collision between goombas and Mario
				if (Collisions::Instance()->Circle(m_goombas[i]->GetCollisionCircle(), my_character_mario->GetCollisionCircle()))
				{
					
					my_character_mario->death();
					my_character_mario->SetAlive(false);

					
				}

				if (Collisions::Instance()->Circle(m_goombas[i]->GetCollisionCircle(), my_character_luigi->GetCollisionCircle()))
				{
					
					
					my_character_luigi->death();
					my_character_luigi->SetAlive(false);
					
				}

				


			}

			if (!m_goombas[i]->GetAlive())
			{
				goombasIndexToDelete = i;

			}

		}

		if (goombasIndexToDelete != -1)
		{
			m_goombas.erase(m_goombas.begin() + goombasIndexToDelete);
		}
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	CharacterKoopa* koopa = new CharacterKoopa(m_renderer, "Images/Koopa.png", m_level_map, position, direction, speed);
		
	m_koopas.push_back(koopa);
}

void GameScreenLevel1::CreateCoins(Vector2D position, float frame_delay)
{
	CharacterCoin* coin = new CharacterCoin(m_renderer, "Images/Coin.png", m_level_map, position, frame_delay);

	m_coins.push_back(coin);
}

void GameScreenLevel1::CreateGoombas(Vector2D position, FACING direction, float speed, float frame_delay)
{
	CharacterGoomba* goomba = new CharacterGoomba(m_renderer, "Images/Goomba.png", m_level_map, position, direction, speed, frame_delay);

	m_goombas.push_back(goomba);
}

void GameScreenLevel1::DoScreenShake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;

	for (int i = 0; i < m_koopas.size(); i++)
	{
		m_koopas[i]->TakeDamage();
	}
}

bool GameScreenLevel1::GameOver(float deltaTime, SDL_Event e)
{
	
	if (!my_character_mario->GetAlive() && !my_character_luigi->GetAlive())
	{
			
		/*Change screen if not*/
		return true;
					
				
	}
	else
	{
		return false;
	}
	
}

bool GameScreenLevel1::Victory(float deltaTime, SDL_Event e)
{
	if (!m_koopas.empty())
	{
		int koopasIndexToDelete = -1;
		for (int i = 0; i < m_koopas.size(); i++)
		{

			if (!m_koopas[i]->GetAlive())
			{
				koopasIndexToDelete = i;
			}


		}

		if (koopasIndexToDelete != -1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
}
