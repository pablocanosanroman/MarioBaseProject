#include "GameScreenLevel1.h"
#include <iostream>





GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel1();
	timeForNextKoopa = KOOPA_SPAWN_TIME;

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

	m_enemies.clear();

	m_coins.clear();

	delete m_level_map;

	m_level_map = nullptr;

}

void GameScreenLevel1::Render() 
{
	
	//draw the enemies
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Render();
	}

	//draw the coins
	for (int i = 0; i < m_coins.size(); i++)
	{
		m_coins[i]->Render();
	}
	//draw a background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);

	//Draw Mario
	my_character_mario->Render();

	//Draw Luigi
	my_character_luigi->Render();

	//Draw POW
	m_pow_block->Render();

	
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	
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
	UpdateEnemies(deltaTime, e);
	UpdateCoins(deltaTime, e);

	timeForNextKoopa -= deltaTime;
	
	
	
	if (timeForNextKoopa <= 0.0f && countKoopa < 5)
	{
			countKoopa++;
			timeForNextKoopa = KOOPA_SPAWN_TIME;
			CreateKoopa(Vector2D(90, 32), FACING_RIGHT, KOOPA_SPEED);
			CreateKoopa(Vector2D(425, 32), FACING_LEFT, KOOPA_SPEED);
	}
	
	
	
};

bool GameScreenLevel1::SetUpLevel1()
{
	
	m_screenshake = false;
	m_background_yPos = 0.0f;
	
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

	//set up koopas
	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);

	CreateCoins(Vector2D(140, 135), ANIMATION_DELAY);
	CreateCoins(Vector2D(160, 135), ANIMATION_DELAY);
	CreateCoins(Vector2D(180, 135), ANIMATION_DELAY);
	CreateCoins(Vector2D(200, 135), ANIMATION_DELAY);
	CreateCoins(Vector2D(220, 135), ANIMATION_DELAY);
	CreateCoins(Vector2D(240, 135), ANIMATION_DELAY);
	CreateCoins(Vector2D(260, 135), ANIMATION_DELAY);
	CreateCoins(Vector2D(280, 135), ANIMATION_DELAY);
	CreateCoins(Vector2D(300, 135), ANIMATION_DELAY);
	CreateCoins(Vector2D(320, 135), ANIMATION_DELAY);
	CreateCoins(Vector2D(340, 135), ANIMATION_DELAY);
	CreateCoins(Vector2D(360, 135), ANIMATION_DELAY);
	
	
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
				DoScreenShake();
				m_pow_block->TakeHit();
				my_character_mario->CancelJump();
			}
		}
	}

	if (Collisions::Instance()->Box(my_character_luigi->GetCollisionBox(), m_pow_block->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailable())
		{
			if (my_character_luigi->IsJumping())
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				my_character_luigi->CancelJump();
			}
		}
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!m_enemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			//check if the enemy is on the bottom row of tiles
			if (m_enemies[i]->GetPosition().y > 300.0f)
			{
				//is the enemy off screen to the left/right?
				if (m_enemies[i]->GetPosition().x + m_enemies[i]->GetWidthSprite() < 1 ||
					m_enemies[i]->GetPosition().x > SCREEN_WIDTH)
				{
					m_enemies[i]->SetAlive(false);
				}

			}
			//now do the update
			m_enemies[i]->Update(deltaTime, e);

			//check to see if enemy collides with player
			if ((m_enemies[i]->GetPosition().y > 300.0f ||
				m_enemies[i]->GetPosition().y <= 64.0f) && (m_enemies[i]->GetPosition().x < 64.0f ||
					m_enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//ignore collisions if behind pipe
			}
			else
			{
				if (Collisions::Instance()->Circle(m_enemies[i]->GetCollisionCircle(), my_character_mario->GetCollisionCircle()))
				{
					if (m_enemies[i]->GetInjured())
					{
						m_enemies[i]->SetAlive(false);
					}
					else
					{
						my_character_mario->death();
						
					}
				}

				if (Collisions::Instance()->Circle(m_enemies[i]->GetCollisionCircle(), my_character_luigi->GetCollisionCircle()))
				{
					if (m_enemies[i]->GetInjured())
					{
						m_enemies[i]->SetAlive(false);
					}
					else
					{
						my_character_luigi->death();
					}
				}
			}

			//if the enemy is no longer alive then schedule it for deletion
			if (!m_enemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}

			
		}
			//remove dead enemies -1 each update
		if (enemyIndexToDelete != -1)
		{
			m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
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
					m_coins[i]->FlipRightwayUp();
					m_coins[i]->SetAlive(false);
					
				}

				if (Collisions::Instance()->Circle(m_coins[i]->GetCollisionCircle(), my_character_luigi->GetCollisionCircle()))
				{
					m_coins[i]->FlipRightwayUp();
					m_coins[i]->SetAlive(false);
				
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

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	CharacterKoopa* koopa = new CharacterKoopa(m_renderer, "Images/Koopa.png", m_level_map, position, direction, speed);
		
	m_enemies.push_back(koopa);
}

void GameScreenLevel1::CreateCoins(Vector2D position, float frame_delay)
{
	CharacterCoin* coin = new CharacterCoin(m_renderer, "Images/Coin.png", m_level_map, position, frame_delay);

	m_coins.push_back(coin);
}

void GameScreenLevel1::DoScreenShake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;

	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->TakeDamage();
	}
}
