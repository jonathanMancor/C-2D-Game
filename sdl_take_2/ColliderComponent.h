#pragma once
#include "Includes.h"


class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	
	//names the of collider type
	std::string tag; 

	TransformComponent* transform;

	ColliderComponent(std::string tag)
	{
		this->tag = tag;
	}

	void Init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->AddComponent<TransformComponent>();
		}
		transform = &entity->GetComponent<TransformComponent>();

		Game::colliders.push_back(this);
	}


	void Update() override
	{
		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);
		collider.w = transform->width * transform->scale;
		collider.h = transform->height * transform->scale;
	}
};