#include "GameScreenManager.h"


GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	m_renderer = renderer;

	m_current_screen = nullptr;

	m_intro_screen_changed = false;

	m_game_over = false;

	m_victory = false;

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

	if (m_current_screen->Victory(deltaTime, e))
	{
		ChangeScreen(SCREEN_VICTORY);
	}

	switch (e.type)
	{
	
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_SPACE:
			if (m_intro_screen_changed == false)
			{
				ChangeScreen(SCREEN_LEVEL1);
				

			}
			
			break;
		case SDLK_r:
			if (m_game_over)
			{
				ChangeScreen(SCREEN_LEVEL1);
			}
			break;
		case SDLK_y:
			if (m_victory)
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

	GameIntroScreen* tempScreen;
	GameScreenLevel1* tempScreen1;
	GameOverScreen* tempScreen2;
	GameScreenVictory* tempScreen3;

	switch (new_screen)
	{
	case SCREEN_INTRO:
		m_game_over = false;
		m_victory = false;
		tempScreen = new GameIntroScreen(m_renderer);
		m_current_screen = (GameScreen*)tempScreen;
		tempScreen = nullptr;
		break;
	case SCREEN_LEVEL1:
		m_intro_screen_changed = true;
		m_game_over = false;
		m_victory = false;
		tempScreen1 = new GameScreenLevel1(m_renderer);
		m_current_screen = (GameScreen*)tempScreen1;
		tempScreen1 = nullptr;
		break;
	case SCREEN_GAMEOVER:
		m_intro_screen_changed = true;
		m_game_over = true;
		m_victory = false;
		tempScreen2 = new GameOverScreen(m_renderer);
		m_current_screen = (GameScreen*)tempScreen2;
		tempScreen2 = nullptr;
		break;
	case SCREEN_VICTORY:
		m_intro_screen_changed = true;
		m_game_over = false;
		m_victory = true;
		tempScreen3 = new GameScreenVictory(m_renderer);
		m_current_screen = (GameScreen*)tempScreen3;
		tempScreen3 = nullptr;
		break;

	default:;
	}
}

