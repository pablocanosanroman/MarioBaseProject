#include "GameScreen.h"
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "constants.h"

GameScreen::GameScreen(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}

GameScreen::~GameScreen() 
{
	m_renderer = nullptr;
}

void GameScreen::Render()
{

}

void GameScreen::Update(float deltaTime, SDL_Event e)
{

}