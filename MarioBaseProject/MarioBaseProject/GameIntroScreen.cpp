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

	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/black.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	m_title_texture = new Texture2D(m_renderer);
	if (!m_title_texture->LoadFromFile("Images/IntroMarioBackground.png"))
	{
		std::cout << "Failure to load title texture!" << std::endl;
		return false;
	}

	return true;
}

void GameIntroScreen::Render()
{
	//draw a background
	m_background_texture->Render(Vector2D(-3, 0), SDL_FLIP_NONE);
	m_title_texture->Render(Vector2D(130, 120), SDL_FLIP_NONE);

}

void GameIntroScreen::Update(float deltaTime, SDL_Event e)
{

}