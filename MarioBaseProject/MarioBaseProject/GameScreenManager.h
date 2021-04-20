#pragma once
#ifndef GAMESCREENMANAGER_H
#define GAMESCREENMANAGER_H

#include <SDL.h>
#include "Commons.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameIntroScreen.h"
#include "GameOverScreen.h"

class GameScreen;

class GameIntroScreen;

class GameScreenLevel1;

class GameOverScreen;

class GameScreenManager
{

public:

	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ChangeScreen(SCREENS new_screen);

private:

	bool intro_screen_changed;
	bool game_over;

	//GameIntroScreen* tempScreen;
	//GameScreenLevel1* tempScreen1;
	//GameOverScreen* tempScreen2;

	SDL_Renderer* m_renderer;

	GameScreen* m_current_screen;

};

#endif //GAMESSCREENMANAGER_H