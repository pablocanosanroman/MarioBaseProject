#include "GameScreenLevel1.h"
#include <iostream>





GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel1();
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete m_background_texture;

	m_background_texture = nullptr;

	delete my_character_mario;

	my_character_mario = nullptr;

	delete my_character_luigi;

	my_character_luigi = nullptr;
}

void GameScreenLevel1::Render() 
{
	//draw a background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);

	my_character_mario->Render();

	my_character_luigi->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//update character
	my_character_mario->Update(deltaTime, e);

	my_character_luigi->Update(deltaTime, e);

	if (Collisions::Instance()->Circle(my_character_mario->GetCollisionCircle(), my_character_luigi->GetCollisionCircle()))
	{
		std::cout << "Circle hit!" << std::endl;
	}

	if (Collisions::Instance()->Box(my_character_mario->GetCollisionBox(), my_character_luigi->GetCollisionBox()))
	{
		std::cout << "Box hit!" << std::endl;
	}

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

	//set up player character
	my_character_mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330));
	
	//set up luigi
	my_character_luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(70, 330));

	return true;
}
