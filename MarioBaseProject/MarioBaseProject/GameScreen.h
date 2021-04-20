#pragma once
#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>

class GameScreen
{
public:

	

	GameScreen(SDL_Renderer* renderer);
	virtual ~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	virtual bool GameOver(float deltaTime, SDL_Event e) { return false; }
	virtual bool Victory(float deltaTime, SDL_Event e) { return false; }

private:

protected:
	SDL_Renderer* m_renderer;


};

#endif //_GAMESCREEN_H