#include "Collisions.h"
#include "Character.h"

//initialise instance to nullptr
Collisions* Collisions::m_instance = nullptr;

Collisions::Collisions()
{

}

Collisions::~Collisions()
{
	m_instance = nullptr;
}

Collisions* Collisions::Instance()
{
	if (!m_instance)
	{
		m_instance = new Collisions;
	}

	return m_instance;
}

// Circle collisions function
bool Collisions::Circle(Circle2D circle1, Circle2D circle2)
{
	//If one of the circles get in the way of the other one->true
	Vector2D vec = Vector2D((circle1.x - circle2.x),
		(circle1.y - circle2.y));

	double distance = sqrt((vec.x * vec.x) + (vec.y * vec.y));

	double combined_distance = (circle1.radius + circle2.radius);

	return distance < combined_distance;
}

//Box collisions function
bool Collisions::Box(Rect2D rect1, Rect2D rect2)
{
	//If one of the rectangles hits the other one-> true
	if (rect1.x < rect2.x + rect2.width &&
		rect1.x + rect1.width > rect2.x &&
		rect1.y < rect2.y + rect2.height &&
		rect1.y + rect1.height > rect2.y)
	{
		return true;
	}
	else
	{
		return false;
	}

}


