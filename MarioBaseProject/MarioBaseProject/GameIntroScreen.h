#pragma once
#ifndef GAMEINTROSCREEN_H_
#define GAMEINTROSCREEN_H_

#include "GameScreen.h"
#include "Commons.h"
#include "Texture2D.h"
#include "GameScreenManager.h"

class Texture2D;

class GameScreenManager;

class GameIntroScreen : GameScreen
{
public:
	GameIntroScreen(SDL_Renderer* renderer);
	~GameIntroScreen();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

private:
	bool SetUpIntro();


	Texture2D* m_background_texture;
	Texture2D* m_title_texture;

	GameScreenManager* m_screen;
};

#endif // !GAMEINTROSCREEN_H_


