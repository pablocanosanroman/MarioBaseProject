#pragma once
#ifndef _TEXTMANAGER_H_
#define _TEXTMANAGER_H_

#include "constants.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <iostream>

class TextManager
{

public:
	TextManager(SDL_Renderer* renderer, int font_size, std::string font_path, TTF_Font* font);
	~TextManager();

	void Update();
	void Render(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect dst);

	void DrawText(int width, int height, std::string score, SDL_Color text_color, SDL_Texture* texture, SDL_Surface* text_surface);

private:

	SDL_Renderer* m_renderer;
	int _font_size;
	std::string _font_path;
	TTF_Font* _font;
	
};


#endif //_TEXTMANAGER_H_