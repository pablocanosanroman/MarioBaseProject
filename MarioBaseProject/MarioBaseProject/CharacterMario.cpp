#include "CharacterMario.h"


CharacterMario::CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map)
{
	m_single_sprite_w = m_texture->GetWidth();
	m_single_sprite_h = m_texture->GetHeight();


}

CharacterMario::~CharacterMario()
{

}



void CharacterMario::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:

			m_moving_left = true;
			break;
		case SDLK_RIGHT:

			m_moving_right = true;
			break;

		case SDLK_UP:
			if (m_can_jump)
			{
				
				Jump();
				
				m_jump_sound->Play();
				
				
			}
			break;
		}
		break;

	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_moving_left = false;
			break;
		case SDLK_RIGHT:
			m_moving_right = false;
			break;
		}
		break;
	}
	
	
	
}
