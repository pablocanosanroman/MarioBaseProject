#include "GameScreenManager.h"


GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	m_renderer = renderer;

	m_current_screen = nullptr;

	tempScreen = new GameIntroScreen(m_renderer);

	tempScreen1 = new GameScreenLevel1(m_renderer);

	tempScreen2 = new GameOverScreen(m_renderer);

	intro_screen_changed = false;

	game_over = false;

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
	
 	if (m_current_screen->GameOver(deltaTime, e))
	{
		ChangeScreen(SCREEN_GAMEOVER);
	}

	switch (e.type)
	{
	
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_SPACE:
			if (intro_screen_changed == false)
			{
				ChangeScreen(SCREEN_LEVEL1);
				

			}
			
			break;
		case SDLK_r:
			if (game_over)
			{
				ChangeScreen(SCREEN_LEVEL1);
			}
			break;
		}
		break;
		
	}

	

	
}


void GameScreenManager::ChangeScreen(SCREENS new_screen)
{
	//clear up the old screen
	if (m_current_screen != nullptr)
	{
		delete m_current_screen;
	}

	//Screen Switch
	

	switch (new_screen)
	{
	case SCREEN_INTRO:
		game_over = false;
		/*tempScreen = new GameIntroScreen(m_renderer);*/
		m_current_screen = (GameScreen*)tempScreen;
		tempScreen = nullptr;
		break;
	case SCREEN_LEVEL1:
		intro_screen_changed = true;
		game_over = false;
	/*	tempScreen1 = new GameScreenLevel1(m_renderer);*/
		m_current_screen = (GameScreen*)tempScreen1;
		tempScreen1 = nullptr;
		break;
	case SCREEN_GAMEOVER:
		intro_screen_changed = true;
		game_over = true;
	/*	tempScreen2 = new GameOverScreen(m_renderer);*/
		m_current_screen = (GameScreen*)tempScreen2;
		tempScreen2 = nullptr;
		break;

	default:;
	}
}

