#pragma once

struct Vector2D
{
	float x;
	float y;

	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2D(float initial_x, float initial_y)
	{
		x = initial_x;
		y = initial_y;
	}
};

struct Rect2D
{
	float x;
	float y;
	float width;
	float height;

	Rect2D(float x_pos, float y_pos, float width, float height)
	{
		x = x_pos;
		y = y_pos;
		this->width = width;
		this->height = height;
	}
};

struct Circle2D
{
	float x;
	float y;
	float radius;

	Circle2D(float x_pos, float y_pos, float radius)
	{
		x = x_pos;
		y = y_pos;
		this->radius = radius;
	}
};

enum SCREENS
{
	SCREEN_INTRO,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_VICTORY,
	SCREEN_GAMEOVER,
	
};

enum FACING
{
	FACING_LEFT,
	FACING_RIGHT
};