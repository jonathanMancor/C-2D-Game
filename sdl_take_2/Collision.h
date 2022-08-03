#pragma once

class ColliderComponent;

class Collision
{
public:
	//axis aligned bounding box
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
};

