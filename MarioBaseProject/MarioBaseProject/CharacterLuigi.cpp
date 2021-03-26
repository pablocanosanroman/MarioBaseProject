#include "CharacterLuigi.h"


CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map)
{
	m_single_sprite_w = m_texture->GetWidth();
	m_single_sprite_h = m_texture->GetHeight();
}

CharacterLuigi::~CharacterLuigi()
{
	
}



void CharacterLuigi::Update(float deltaTime, SDL_Event e)
{

	Character::Update(deltaTime, e);

	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:

			m_moving_left = true;
			break;
		case SDLK_d:

			m_moving_right = true;
			break;

		case SDLK_w:
			if (m_can_jump)
			{
				m_jump_sound->Play();
				Jump();

			}
			break;
		}
		break;

	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
		m_moving_left = false;
			break;
		case SDLK_d:
			m_moving_right = false;
			break;
		}
		break;
	}

	
}


