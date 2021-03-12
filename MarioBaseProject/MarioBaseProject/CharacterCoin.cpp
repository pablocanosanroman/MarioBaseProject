#include "CharacterCoin.h"

CharacterCoin::CharacterCoin(SDL_Renderer* renderer, std::string imagePath, LevelMap* map,
	Vector2D start_position, float frame_delay) : Character(renderer, imagePath, start_position, map)
{
	
	m_position = start_position;
	m_frame_delay = frame_delay;
	m_current_frame = 0.0f;


	m_single_sprite_w = m_texture->GetWidth() / 3;
	m_single_sprite_h = m_texture->GetHeight();
}

void CharacterCoin::Render()
{

	//get the portion of the sprite sheet you want to draw 
	//{xPos, yPos, width of sprite, height of sprite}
	SDL_Rect portion_of_sprite = { m_single_sprite_w* m_current_frame, 0, m_single_sprite_w, m_single_sprite_h };

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

void CharacterCoin::Update(float deltaTime, SDL_Event e)
{

	m_frame_delay -= deltaTime;
	if (m_frame_delay <= 0.0f)
	{
		//reset frame delay count
		m_frame_delay = ANIMATION_DELAY;

		//move the frame over
		m_current_frame++;

		//loop frame around if it goes beyond the number of frames
		if (m_current_frame > 2)
		{
			m_current_frame = 0;
		}
	}
}

void CharacterCoin::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = INITIAL_JUMP_FORCE_SMALL;
		m_jumping = true;
		m_can_jump = false;
	}
}

void CharacterCoin::FlipRightwayUp()
{
	if (m_facing_direction == FACING_LEFT)
	{
		m_facing_direction == FACING_RIGHT;
	}
	else if (m_facing_direction == FACING_RIGHT)
	{
		m_facing_direction == FACING_LEFT;
	}

	
	Jump();
}