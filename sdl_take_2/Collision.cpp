#include "Includes.h"

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
	if (recA.x + recA.w >= recB.x &&
		recA.y + recA.h >= recB.y &&
		recB.x + recB.w >= recA.x &&
		recB.y + recB.h >= recA.h) {
		return true;
	}
	else { return false; }
		
}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{
	if (AABB(colA.collider, colB.collider))
	{
		std::cout << colA.tag << " hit: " << colB.tag << "\n";
		return true;
	}
	else
	{
		return false;
	}
}
