#include "CharacterLuigi.h"


CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map, float frame_delay) : Character(renderer, imagePath, start_position, map)
{
	m_single_sprite_w = m_texture->GetWidth() / 5;
	m_single_sprite_h = m_texture->GetHeight();

	m_frame_delay = frame_delay;
	m_current_frame = 0.0f;
}

CharacterLuigi::~CharacterLuigi()
{
	
}

void CharacterLuigi::Render()
{
	//get the portion of the sprite sheet you want to draw 
	//{xPos, yPos, width of sprite, height of sprite}
	SDL_Rect portion_of_sprite = { m_single_sprite_w * m_current_frame, 0, m_single_sprite_w, m_single_sprite_h };

	//determine where you want it drawn
	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	//then draw it facing the correct direction
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterLuigi::Update(float deltaTime, SDL_Event e)
{

	Character::Update(deltaTime, e);

	m_frame_delay -= deltaTime;

	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:

			m_moving_left = true;

			if (m_frame_delay <= 0.0f)
			{
				//reset frame delay count
				m_frame_delay = ANIMATION_DELAY;

				//move the frame over
				m_current_frame++;

				//loop frame around if it goes beyond the number of frames
				if (m_current_frame > 3)
				{
					m_current_frame = 1;
				}
			}

			break;
		case SDLK_d:

			m_moving_right = true;

			if (m_frame_delay <= 0.0f)
			{
				//reset frame delay count
				m_frame_delay = ANIMATION_DELAY;

				//move the frame over
				m_current_frame++;

				//loop frame around if it goes beyond the number of frames
				if (m_current_frame > 3)
				{
					m_current_frame = 1;
				}
			}

			break;

		case SDLK_w:
			if (m_can_jump)
			{
				
				m_current_frame = 4.0f;
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
			m_current_frame = 0.0f;
			break;
		case SDLK_d:
			m_moving_right = false;
			m_current_frame = 0.0f;
			break;
		}
		break;
	}

	
	if (m_position.x < 0)
	{
		m_position.x = SCREEN_WIDTH - 20;
	}
	else if (m_position.x > SCREEN_WIDTH - 20)
	{
		m_position.x = 0.0f;
	}
}


