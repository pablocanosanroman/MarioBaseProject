#pragma once
#ifndef _CHARACTER_H
#define _CHARACTER_H

#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include "Texture2D.h"
#include "LevelMap.h"


class Texture2D;

class Character
{
protected:

	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	FACING m_facing_direction;
	bool m_moving_left;
	bool m_moving_right;
	bool m_jumping;
	bool m_can_jump;
	bool m_alive;
	float m_jump_force;
	float m_collision_radius;
	float m_movement_speed;

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	virtual void AddGravity(float deltaTime);
	virtual void Jump();

public:

	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void SetPosition(Vector2D new_position);
	float GetCollisionRadius();
	Vector2D GetPosition();
	Rect2D GetCollisionBox() {
		return Rect2D(m_position.x, m_position.y,
			m_texture->GetWidth(), m_texture->GetHeight());
	}
	Circle2D GetCollisionCircle() {
		return Circle2D(m_position.x, m_position.y, GetCollisionRadius());
	}

	bool IsJumping() { return m_jumping; }
	void CancelJump() { m_jumping = false; }

	bool GetAlive() { return m_alive; }
	void SetAlive(bool isAlive);
	

private:

	
	LevelMap* m_current_level_map;
};

#endif _CHARACTER_H //_CHARACTER_H
