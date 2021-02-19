#include "CharacterLuigi.h"
#include "Texture2D.h"
#include "constants.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position) : Character(renderer, imagePath, start_position)
{
	m_renderer = renderer;

	m_position = start_position;

	m_texture = new Texture2D(m_renderer);

	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cout << "The image couldn't be loaded" << std::endl;
	}

	m_facing_direction == FACING_RIGHT;

	m_moving_left = false;
	m_moving_right = false;
}

CharacterLuigi::~CharacterLuigi()
{
	m_renderer = nullptr;
}

void CharacterLuigi::Render()
{
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(m_position, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterLuigi::Update(float deltaTime, SDL_Event e)
{
	//Gravedad
	AddGravity(deltaTime);

	//deal with jumping first
	if (m_jumping)
	{


		//adjust position
		m_position.y -= m_jump_force * deltaTime;

		//reduce jump force
		m_jump_force -= JUMP_FORCE_DECRECEMENT * deltaTime;

		//is jump force 0?
		if (m_jump_force <= 0.0f)
		{
			m_jumping = false;
		}
	}

	if (m_moving_left)
	{
		MoveLeft(deltaTime);
	}
	else if (m_moving_right)
	{
		MoveRight(deltaTime);
	}
	

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


void CharacterLuigi::SetPosition(Vector2D new_position)
{
	m_position = new_position;
}

Vector2D CharacterLuigi::GetPosition()
{
	return m_position;
}


void CharacterLuigi::MoveLeft(float deltaTime)
{
	m_facing_direction = FACING_LEFT;
	m_position.x -= deltaTime * MOVEMENTSPEED;
}

void CharacterLuigi::MoveRight(float deltaTime)
{
	m_facing_direction = FACING_RIGHT;
	m_position.x += deltaTime * MOVEMENTSPEED;
}

void CharacterLuigi::AddGravity(float deltaTime)
{
	if ((m_position.y + 64) <= SCREEN_HEIGHT)
	{
		m_position.y += GRAVITY * deltaTime;
	}
	else
	{
		m_can_jump = true;
	}
}

void CharacterLuigi::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = INITIAL_JUMP_FORCE;
		m_jumping = true;
		m_can_jump = false;
	}

}