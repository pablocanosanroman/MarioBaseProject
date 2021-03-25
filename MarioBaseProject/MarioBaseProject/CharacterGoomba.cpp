#include "CharacterGoomba.h"


CharacterGoomba::CharacterGoomba(SDL_Renderer* renderer, std::string imagePath, LevelMap* map,
	Vector2D start_position, FACING start_facing, float movement_speed, float frame_delay) : Character(renderer, imagePath, start_position, map)
{
	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_position = start_position;

	m_single_sprite_w = m_texture->GetWidth() / 2;
	m_single_sprite_h = m_texture->GetHeight();
}

CharacterGoomba::~CharacterGoomba()
{

}

void CharacterGoomba::Render()
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

void CharacterGoomba::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);
	
	m_frame_delay -= deltaTime;

	if (m_frame_delay <= 0.0f)
	{
		//reset frame delay count
		m_frame_delay = ANIMATION_DELAY;

		//move the frame over
		m_current_frame++;

		//loop frame around if it goes beyond the number of frames
		if (m_current_frame > 1)
		{
			m_current_frame = 0;
		}
	}

	if (m_facing_direction == FACING_LEFT)
	{
		m_moving_left = true;
		m_moving_right = false;

		
		
	}
	else if (m_facing_direction == FACING_RIGHT)
	{
		m_moving_right = true;
		m_moving_left = false;


	}

	if ((m_position.x <= 0 || m_position.x + m_single_sprite_w >= SCREEN_WIDTH) && m_position.y < 331 )
	{
		if (m_facing_direction == FACING_LEFT)
		{
			m_facing_direction = FACING_RIGHT;
			m_moving_right = true;
			m_moving_left = false;


		}
		else if (m_facing_direction == FACING_RIGHT)
		{
			
			m_facing_direction = FACING_LEFT;
			m_moving_left = true;
			m_moving_right = false;

		}
	}
}