#include "GameIntroScreen.h"
#include <iostream>

GameIntroScreen::GameIntroScreen(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpIntro();
}

GameIntroScreen::~GameIntroScreen()
{
	delete m_background_texture;

	m_background_texture = nullptr;
}

bool GameIntroScreen::SetUpIntro()
{
	m_background_yPos = 0.0f;
	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/black.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	return true;
}

void GameIntroScreen::Render()
{
	//draw a background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);
}

void GameIntroScreen::Update(float deltaTime, SDL_Event e)
{
	
}