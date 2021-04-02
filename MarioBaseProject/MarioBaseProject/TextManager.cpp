#include "TextManager.h"

TextManager::TextManager(SDL_Renderer* renderer, int font_size, std::string font_path, TTF_Font* font)
{
	m_renderer = renderer;
	_font_size = font_size;
	_font_path = font_path;
	_font = font;

}

TextManager::~TextManager()
{
	
}

void TextManager::Update()
{
	
}

void TextManager::Render(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect dst)
{
	SDL_RenderCopy(renderer, texture, NULL, &dst);
}

void TextManager::DrawText(int width, int height, std::string score, SDL_Color text_color, SDL_Texture* texture, SDL_Surface* text_surface)
{

	//check to see that the font was loaded correctly
	if (_font == NULL)
	{
		std::cerr << "Failed the load the font!\n";
		std::cerr << "SDL_TTF Error: " << TTF_GetError() << "\n";
	}
	else
	{
		//now create a surface from the font
		text_surface = TTF_RenderText_Solid(_font, score.c_str(), text_color);
		

		//render the text surface
		if (text_surface == NULL)
		{
			std::cerr << "Failed to render text surface! \n";
			std::cerr << "SDL_TTF error!" << TTF_GetError() << "\n";

		}
		else
		{
			//create a texture from the surface
			texture = SDL_CreateTextureFromSurface(m_renderer, text_surface);
		

			if (texture == NULL)
			{
				std::cerr << "Unable to create texture from rendered text!\n";
			}
			else
			{
				width = text_surface->w; //assign the width of the texture
				height = text_surface->h; //assign the height of the texture
				
			}

			//Destroy the surface
			SDL_FreeSurface(text_surface);
			
		}

	}
}