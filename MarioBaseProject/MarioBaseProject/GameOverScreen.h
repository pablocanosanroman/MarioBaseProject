#pragma once
#ifndef GAMEOVERSCREEN_H_
#define GAMEOVERSCREEN_H_

#include "GameScreen.h"
#include "Commons.h"
#include "Texture2D.h"
#include "TextManager.h"
#include <string>

class Texture2D;

class TextManager;

class GameOverScreen : GameScreen
{
public:
	GameOverScreen(SDL_Renderer* renderer);
	~GameOverScreen();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

private:
	bool SetUpGameOver();

	int game_over_text_x;
	int game_over_text_y;
	int restart_text_x;
	int restart_text_y;
	int text_width;
	int text_height;
	int font_size_game_over;
	int font_size_restart;
	std::string font_path;
	std::string game_over_message;
	std::string restart_message;

	SDL_Color text_color;

	Texture2D* m_background_texture;
	TextManager* m_game_over_text;
	TextManager* m_restart_text;


};

#endif // !GAMEOVERSCREEN_H_

