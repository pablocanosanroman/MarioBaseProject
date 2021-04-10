#include "TextManager.h"

TextManager::TextManager(SDL_Renderer* renderer, int font_size, std::string font_path, std::string message, SDL_Color color)
{
	_text_texture = DrawText(renderer, font_path, font_size, message, color);
	SDL_QueryTexture(_text_texture, nullptr, nullptr, &_text_rect.w, &_text_rect.h);

}

TextManager::~TextManager()
{
	
}

void TextManager::Update()
{
	
	
}

void TextManager::Render(int x, int y, SDL_Renderer* renderer)
{
	_text_rect.x = x;
	_text_rect.y = y;
	SDL_RenderCopy(renderer, _text_texture, nullptr, &_text_rect);
}

SDL_Texture* TextManager::DrawText(SDL_Renderer* renderer, std::string font_path, int font_size, std::string message, SDL_Color color)
{
	TTF_Font* font = TTF_OpenFont(font_path.c_str(), font_size);
	//check to see that the font was loaded correctly
	if (font == NULL)
	{
		std::cerr << "Failed the load the font!\n";
		std::cerr << "SDL_TTF Error: " << TTF_GetError() << "\n";
	}
	else
	{
		//now create a surface from the font
		SDL_Surface* text_surface = TTF_RenderText_Solid(font, message.c_str(), color);
		

		//render the text surface
		if (text_surface == NULL)
		{
			std::cerr << "Failed to render text surface! \n";
			std::cerr << "SDL_TTF error!" << TTF_GetError() << "\n";

		}
		else
		{
			//create a texture from the surface
			SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
		

			if (text_texture == NULL)
			{
				std::cerr << "Unable to create texture from rendered text!\n";
			}

			//Destroy the surface
			SDL_FreeSurface(text_surface);

			return text_texture;
			
		}

	}
}