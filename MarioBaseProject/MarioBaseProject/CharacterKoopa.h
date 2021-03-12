#pragma once
#ifndef _CHARACTERKOOPA_H
#define _CHARACTERKOOPA_H

#include "Character.h"

class CharacterKoopa : public Character
{
private:


	bool m_injured;
	float m_injured_time;

	void FlipRightwayUp();


public:
	CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, LevelMap* map,
		Vector2D start_position, FACING start_facing, float movement_speed);

	~CharacterKoopa();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

	void TakeDamage();
	void Jump();
	bool GetInjured() { return m_injured; }
};


#endif // !_CHARACTERKOOPA_H



