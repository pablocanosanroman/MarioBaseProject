#pragma once
#ifndef _CHARACTERLUIGI_H
#define _CHARACTERLUIGI_H


#include "Character.h"

class CharacterLuigi : public Character
{
protected:

	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	bool m_moving_left;
	bool m_moving_right;
	bool m_jumping;
	bool m_can_jump;
	float m_jump_force;

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	virtual void AddGravity(float deltaTime);
	virtual void Jump();

public:

	CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position);
	~CharacterLuigi();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();

private:

	FACING m_facing_direction;
};

#endif _CHARACTERLUIGI_H // _CHARACTERLUIGI_H

