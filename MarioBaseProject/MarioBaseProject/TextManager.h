#pragma once
#ifndef _TEXTMANAGER_H_
#define _TEXTMANAGER_H_

#include "constants.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>

class TextManager
{

public:
	TextManager(SDL_Renderer* renderer, int font_size, std::string font_path, std::string message, SDL_Color color);
	~TextManager();

	void Update(SDL_Renderer* renderer, int font_size, std::string font_path, std::string message, SDL_Color color);
	void Render(int x, int y, SDL_Renderer* renderer);

	static SDL_Texture* DrawText(SDL_Renderer* renderer, std::string font_path, int font_size, std::string message, SDL_Color color);

private:

	//SDL_Renderer* m_renderer;
	////int _font_size;
	////std::string _font_path;
	////TTF_Font* _font;
	//std::string _message;
	SDL_Texture* _text_texture = nullptr;
	SDL_Rect _text_rect;
	
};


#endif //_TEXTMANAGER_H_