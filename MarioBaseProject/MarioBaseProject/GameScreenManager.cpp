#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameIntroScreen.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	m_renderer = renderer;

	m_current_screen = nullptr;

	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager()
{
	m_renderer = nullptr;

	delete m_current_screen;

	m_current_screen = nullptr;
}

void GameScreenManager::Render()
{
	m_current_screen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	m_current_screen->Update(deltaTime, e);
}

void GameScreenManager::ChangeScreen(SCREENS new_screen)
{
	//clear up the old screen
	if (m_current_screen != nullptr)
	{
		delete m_current_screen;
	}

	GameIntroScreen* tempScreen;
	GameScreenLevel1* tempScreen1;

	switch (new_screen)
	{
	case SCREEN_INTRO:
		tempScreen = new GameIntroScreen(m_renderer);
		m_current_screen = (GameScreen*)tempScreen;
		tempScreen = nullptr;

	case SCREEN_LEVEL1:
		tempScreen1 = new GameScreenLevel1(m_renderer);
		m_current_screen = (GameScreen*) tempScreen1;
		tempScreen1 = nullptr;
	default:;
	}
}