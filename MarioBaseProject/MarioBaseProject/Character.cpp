#include "Character.h"
#include "constants.h"

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map)
{
	//Initialize all variables
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

	m_collision_radius = 15.0f;

	m_current_level_map = map;

	m_alive = true;

	m_jump_sound = new SoundEffect();
	m_jump_sound->Load("Music/Jump.wav");
}

Character::~Character()
{
	m_renderer = nullptr;

	delete m_jump_sound;
	
}

void Character::Render()
{
	//Render depending on the facing
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(m_position, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	}
}

void Character::Update(float deltaTime, SDL_Event e)
{
	
	//collisions position variables
	int centralX_position = (int)(m_position.x + (m_single_sprite_w * 0.5)) /
		TILE_WIDTH;
	int foot_position = (int)(m_position.y + m_single_sprite_h) / TILE_HEIGHT;

	//deal with gravity
	if (m_current_level_map->GetTileAt(foot_position, centralX_position) == 0)
	{
		AddGravity(deltaTime);
	}
	else
	{
		//collided with ground so we can jump again
		m_can_jump = true;
	}

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
	
	//Code to make characters move
	if (m_moving_left)
	{
		MoveLeft(deltaTime);
	}
	else if (m_moving_right)
	{
		MoveRight(deltaTime);
	}



}

void Character::SetPosition(Vector2D new_position)
{
	m_position = new_position;
}

Vector2D Character::GetPosition()
{
	return m_position;
}


void Character::MoveLeft(float deltaTime)
{
	m_facing_direction = FACING_LEFT;
	m_position.x -= deltaTime * MOVEMENTSPEED;
}

void Character::MoveRight(float deltaTime)
{
	m_facing_direction = FACING_RIGHT;
	m_position.x += deltaTime * MOVEMENTSPEED;
}

void Character::AddGravity(float deltaTime)
{
	if ((m_position.y + 42) <= SCREEN_HEIGHT)
	{
		m_position.y += GRAVITY * deltaTime;
	}
	else
	{
		m_can_jump = true;
	}
}

void Character::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = INITIAL_JUMP_FORCE;
		m_jumping = true;
		m_can_jump = false;
	}
	
}

float Character::GetCollisionRadius()
{
	return m_collision_radius;
}

void Character::SetAlive(bool isAlive)
{
	m_alive = isAlive;
}

void Character::death()
{
	m_position.x = -300;
	m_position.y = 3000;

	while (m_jumping)
	{
		CancelJump();
	}
	
}